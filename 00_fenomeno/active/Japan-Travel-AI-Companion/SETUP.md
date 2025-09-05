# 미야코지마 여행 AI 컴패니언 - 설정 가이드

## 📱 ChatGPT Projects 설정 (5분)

### 1단계: 프로젝트 생성
```
1. ChatGPT Plus → Projects 탭
2. "New Project" → "Miyakojima Trip Assistant" 
3. Model: GPT-5 선택
4. Voice Mode: 활성화
5. Vision Mode: 활성화
```

### 2단계: 파일 업로드
**Instructions 탭:**
- `instructions/MASTER_INSTRUCTIONS.md`

**Knowledge 탭 (중요순 업로드):**
- `knowledge_base/personal_travel_info.md` (실제 여행정보)
- `knowledge_base/miyakojima_guide.md` (관광지 가이드)
- `knowledge_base/japanese_phrases.md` (일본어 표현)
- `knowledge_base/emergency_info.md` (응급상황)
- `data/poi_database.csv` (주요 장소 좌표)
- `data/route_plans.json` (추천 경로)

## 🎯 사용법

### 음성 모드 (즉시 통역)
- "이거 뭐예요?" → 즉시 일본어 번역
- "화장실 어디예요?" → GPT-4o 엔진으로 빠른 응답

### 텍스트/이미지 모드 (상세 분석)
- 메뉴판 사진 업로드 → GPT-5로 상세 번역+추천
- "맛집 추천해줘" → 개인정보 기반 맞춤 추천

### 응급상황 (자동 감지)
- "아파요", "도움" → 자동으로 high reasoning 모드
- 병원 위치, 교통편, 연락처 즉시 제공

## 📊 개인정보 입력

**필수 정보:**
- 여행 일정: 2025년 9월 27일 ~ 10월 1일
- 숙소: [예약 후 입력]
- 항공편: 진에어 LJ0357/0358
- 알레르기/건강: [개인별 입력]
- 음식 선호도: [개인별 입력]

## 🔧 최적화 팁

- **빠른 통역**: 음성 사용 (GPT-4o, <600ms)
- **상세 분석**: 텍스트 사용 (GPT-5, 정확도 우선)
- **이미지 번역**: 사진 업로드 후 "번역해줘"
- **응급상황**: "도움", "아파" 등 키워드로 즉시 대응

---

**🎯 목표**: 언어 장벽 없는 완벽한 미야코지마 여행