# 🗣️ Realtime API 기반 통역 시스템 설계

## 🎯 핵심 아키텍처

### **3방향 통역 플로우**
```
한국인(A) ←→ AI 중계봇 ←→ 일본인(B)
                ↕
             영어 지원
```

### **실시간 처리 파이프라인**
```
음성입력 → 언어감지 → 텍스트변환 → 번역 → 음성출력
    ↓          ↓         ↓        ↓       ↓
 Realtime → Language → Whisper → GPT-5 → TTS
```

## 🔧 기술적 구현

### **1. Realtime API 설정**
```javascript
// 기본 세션 설정
const session = {
    model: "gpt-realtime",
    instructions: `
# Role & Objective
당신은 한국인 커플과 일본인 사이의 실시간 통역사입니다.
자연스럽고 정확한 번역으로 원활한 소통을 도와주세요.

# Personality & Tone
- 친근하고 정중한 통역사
- 빠르고 정확한 번역
- 문화적 뉘앙스 고려

# Language Detection & Translation Rules
1. 한국어 감지 시 → 일본어로 번역
2. 일본어 감지 시 → 한국어로 번역  
3. 영어 감지 시 → 상황에 맞게 한국어 또는 일본어로
4. 번역 불가능한 경우 → "죄송합니다, 다시 말씀해 주세요"

# Context-Aware Translation
- 식당: 메뉴, 주문, 결제 관련 용어 우선
- 숙소: 체크인, 편의시설 관련 용어 우선
- 교통: 방향, 시간, 요금 관련 용어 우선
- 쇼핑: 가격, 크기, 색상 관련 용어 우선

# Translation Output Format
"[번역] 번역된 내용"
"[해설] 문화적 설명 (필요시)"
`,
    voice: "shimmer", // 자연스러운 음성
    tools: []
};
```

### **2. 언어 감지 & 자동 전환**
```javascript
class LanguageDetector {
    detectLanguage(audioInput) {
        // 음성 기반 언어 감지
        return {
            language: 'ko' | 'ja' | 'en',
            confidence: 0.95,
            text: "감지된 텍스트"
        };
    }
    
    getTranslationDirection(detected) {
        const directions = {
            'ko': 'ja',  // 한국어 → 일본어
            'ja': 'ko',  // 일본어 → 한국어
            'en': 'auto' // 영어 → 상황별
        };
        return directions[detected];
    }
}
```

### **3. 상황별 맞춤 프롬프트**
```javascript
const contextualPrompts = {
    restaurant: `
# 식당 상황 특화 통역
- 메뉴 설명 시 재료, 맛, 알레르기 정보 포함
- 주문 확인 시 정확한 수량, 옵션 전달
- 계산서 관련 용어 정확히 번역
- 일본 식당 에티켓 간단히 안내
    
# 자주 사용되는 표현
한국어 → 일본어:
- "이것 주세요" → "これをください"
- "얼마예요?" → "いくらですか?"
- "맛있어요" → "美味しいです"
`,
    
    accommodation: `
# 숙소 상황 특화 통역  
- 체크인/아웃 시간 정확히 전달
- 룸서비스, 편의시설 문의 지원
- WiFi, 조식 등 실용 정보 우선
- 일본 호텔 매너 간단 안내
`,
    
    transportation: `
# 교통 상황 특화 통역
- 목적지, 소요시간, 요금 정확히 전달  
- 대중교통 이용법 설명
- 택시 호출, 방향 지시 지원
- 일본 교통 규칙 간단 안내
`
};
```

### **4. 멀티모달 지원 (카메라 번역)**
```javascript
class CameraTranslator {
    async translateImage(imageData) {
        const response = await openai.chat.completions.create({
            model: "gpt-4o",
            messages: [
                {
                    role: "user", 
                    content: [
                        {
                            type: "text",
                            text: `
이미지 속 일본어 텍스트를 한국어로 번역해주세요.

출력 형식:
[원문] 일본어 텍스트
[번역] 한국어 번역  
[설명] 간단한 설명 (메뉴/간판/표지판 등)
`
                        },
                        {
                            type: "image_url",
                            image_url: { url: imageData }
                        }
                    ]
                }
            ]
        });
        
        return response.choices[0].message.content;
    }
}
```

## 🎯 실제 사용 시나리오

### **시나리오 1: 식당에서 주문**
```
[사용자] "저기요, 이거 뭐예요?" (메뉴를 가리키며)
[AI → 일본어] "すみません、これは何ですか?"
[직원] "それは沖縄そばです"  
[AI → 한국어] "[번역] 그것은 오키나와 소바입니다"
[AI → 해설] "오키나와의 전통 면요리로, 돼지고기 육수를 사용합니다"
```

### **시나리오 2: 길 묻기**
```
[사용자] "미야코지마 해변으로 어떻게 가요?"
[AI → 일본어] "宮古島のビーチにはどうやって行きますか?"
[현지인] "バスで30分くらいです"
[AI → 한국어] "[번역] 버스로 30분 정도 걸립니다"
```

### **시나리오 3: 응급상황**
```
[사용자] "병원이 어디에 있어요? 급해요!"
[AI → 일본어] "病院はどこにありますか？緊急です！"
[AI → 추가정보] "가장 가까운 병원: 미야코지마 병원 (3km)"
```

## 🔄 오류 처리 & 백업

### **연결 불량 시 대응**
```javascript
class OfflineBackup {
    basicPhrases = {
        ko_to_ja: {
            "안녕하세요": "こんにちは",
            "감사합니다": "ありがとうございます", 
            "죄송합니다": "すみません",
            "화장실이 어디예요?": "トイレはどこですか？"
        },
        ja_to_ko: {
            "こんにちは": "안녕하세요",
            "ありがとうございます": "감사합니다"
        }
    };
    
    fallbackTranslate(text, direction) {
        return this.basicPhrases[direction][text] || 
               "연결이 불안정합니다. 다시 시도해 주세요.";
    }
}
```

## ⚡ 성능 최적화

### **응답속도 향상**
- **병렬처리**: 언어감지 + 번역 동시 실행
- **캐싱**: 자주 사용되는 표현 미리 번역
- **압축**: 음성 데이터 최적화
- **로컬저장**: 오프라인 필수 표현 저장

### **배터리 절약**
- **음성감지 최적화**: 불필요한 녹음 방지
- **화면 밝기 자동조절**: 사용 패턴 학습
- **절전모드**: 5분 무사용 시 대기모드

---
*설계 완료일: 2025-01-15*  
*예상 개발기간: 2주*