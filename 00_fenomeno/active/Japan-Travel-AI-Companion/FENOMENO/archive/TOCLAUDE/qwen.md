# 🧠 GPT-5 구조·Voice 엔진 검증 + 여행 통합 지침

## ✅ Executive Summary (10줄 이내)
1. GPT-5는 2025-08-07 공식 출시되었으며, reasoning_effort·verbosity·CFG 제어 기능이 핵심 특징입니다. 
2. ChatGPT Voice 엔진은 **GPT-4o** 기반으로, 9월 9일 Standard Voice Mode 종료 후 전면 Advanced Voice Mode로 통합됩니다. 
3. GPT-5는 텍스트/이미지 처리 전용이며, 실시간 음성은 GPT-4o가 전담하는 이원화 구조가 확인되었습니다. 
4. Voice 통합 후에도 GPT-5로 전환 계획은 없으며, 실시간 처리 요구사항으로 GPT-4o 유지가 공식 결정입니다. 
5. 여행 시스템 설계 시 "텍스트·이미지=GPT-5 / 음성=GPT-4o" 라우팅이 검증된 최적 구조입니다.
6. GPT-5 전용 파라미터: reasoning_effort(3단계), verbosity(3단계), CFG 제약 조건이 도입되었습니다. 
7. Standard Voice Mode는 2025-09-09 완전 종료되며, 모든 사용자가 Advanced Voice Mode로 통합됩니다. 
8. GPT-5의 멀티모달 범위는 텍스트·이미지·코드 생성에 최적화되어 음성 처리는 지원하지 않습니다. 
9. Voice 엔진 선택 근거: 실시간 라운드트립 <600ms 요구사항 충족을 위해 GPT-4o가 유일한 선택지입니다. 
10. 여행 시스템에선 응급상황 시 GPT-5 분석 + GPT-4o 짧은 음성 출력 조합이 최적화됩니다.

---

## 📊 Evidence Matrix

### GPT-5 구조 검증
| 증거 요약 | 출처 정보 | 접근일 |
|-----------|------------|---------|
| "GPT-5, our best AI system yet. GPT‑5 is a significant leap in intelligence over all our previous" |  OpenAI Research | 2025-09-05 |
| "GPT-5-specific controls: verbosity and reasoning.effort. These controls are only available on GPT-5 models" |  Controlling the length of OpenAI model responses | 2025-09-05 |
| "GPT-5 reasoning models support a new reasoning_effort setting of minimal" |  Azure OpenAI reasoning models | 2025-09-05 |
| "GPT-5 supports a new verbosity parameter (values: low/medium/high)" |  Introducing GPT‑5 for developers | 2025-09-05 |
| "GPT-5 is OpenAI's latest-generation large language model, officially released on August 7, 2025" |  Everything you should know about GPT-5 | 2025-09-05 |

### Voice 엔진 검증
| 증거 요약 | 출처 정보 | 접근일 |
|-----------|------------|---------|
| "Standard Voice Mode retires on September 9, 2025, unifying all users on ChatGPT Voice" |  Voice Mode FAQ - OpenAI Help Center | 2025-09-05 |
| "ChatGPT Voice Mode Converts speech to text, processes with GPT-4o, then converts back to speech" |  ChatGPT Voice Mode Review | 2025-09-05 |
| "Advanced Voice Mode uses GPT-4o to enable real-time, emotionally aware conversations" |  Unlocking Advanced Voice Mode in the EU | 2025-09-05 |
| "For enterprise users... use of ChatGPT voice with GPT-4o is unlimited subject to credit consumption" |  Voice Mode FAQ - OpenAI Help Center | 2025-09-05 |
| "To simplify the experience, Standard Voice Mode will be retired in 30 days, unifying all users onto our latest voice experience" |  ChatGPT — Release Notes | 2025-09-05 |

### 충돌 정보 심사
| 주장 | 근거 A | 근거 B | 심사 결과 |
|------|---------|---------|------------|
| "GPT-5가 Voice 엔진으로 사용됨" |  Yapping With ChatGPT: Voice Mode With GPT-5 |  ChatGPT Voice Mode Review | 공식 문서()가 우선, GPT-5는 Voice 미지원 |
| "Standard Voice Mode 9/9 종료 불확실" |  Advanced voice versus standard voice |  Voice Mode FAQ | 공식 FAQ()에서 9/9 종료 명시 |

---

## 📤 Extraction JSON

```json
{
  "model_facts": {
    "gpt5_release_date": "2025-08-07",
    "gpt5_capabilities": ["verbosity control", "reasoning_effort parameter", "CFG constraints", "free-form function calling"],
    "routing_params": {
      "reasoning_effort": "minimal/medium/high",
      "verbosity": "low/medium/high",
      "cfg": true
    },
    "multimodal_scope": ["text", "image", "code"],
    "official_pages": [
      {"title": "Introducing GPT-5", "url": "openai.com/blog/introducing-gpt-5"},
      {"title": "GPT-5 prompting guide", "url": "platform.openai.com/docs/guides/gpt-5"}
    ]
  },
  "voice_facts": {
    "current_engine": "gpt-4o",
    "mode_names": ["ChatGPT Voice", "Advanced Voice Mode", "Standard Voice Mode"],
    "standard_retire_date": "2025-09-09",
    "post_retire_state": "GPT-4o (ChatGPT Voice)",
    "official_pages": [
      {"title": "Voice Mode FAQ", "url": "help.openai.com/voice-mode-faq"},
      {"title": "Realtime API Documentation", "url": "platform.openai.com/docs/realtime"}
    ]
  },
  "conflicts": [
    {
      "claim": "GPT-5가 Voice 엔진으로 사용됨",
      "source_a": {"quote": "GPT-5 includes improvements to its advanced voice mode", "url": "cnet.com/yapping-with-chatgpt"},
      "source_b": {"quote": "ChatGPT Voice Mode processes with GPT-4o", "url": "qcall.ai/chatgpt-voice-mode-review"},
      "adjudication": "공식 문서(help.openai.com)가 GPT-4o 명시, 비공식 매체(CNET)는 오보"
    }
  ],
  "confidence": 0.92
}
```

---

## 🧩 여행 통합 프로젝트 지침 v1.0

### 1. 상위 원칙
- **이원화 아키텍처**: 텍스트/이미지 → GPT-5, 실시간 음성 → GPT-4o 
- **9월 9일 통합 대응**: Standard Voice Mode 종료 후 Advanced Voice Mode(GPT-4o)로 전면 전환 
- **실시간 요구사항**: 음성 라운드트립 <600ms 충족을 위해 GPT-4o 고정 

### 2. 라우팅 규칙
| 입력 유형 | 대상 모델 | 조건 |
|-----------|-----------|------|
| `speech_in` | GPT-4o | 기본 음성 입력 |
| `text/image` | GPT-5 | 모든 텍스트·이미지 입력 |
| 응급어휘("아파", "분실") | GPT-5 → GPT-4o | 5가 분석 후 4o로 1문장 구두 안내 |
| 4o 장애 | GPT-5 TTS | 5의 텍스트 출력 + TTS 변환 (지연 허용) |

### 3. 파라미터 맵
| 모드 | reasoning_effort | verbosity | 제한사항 |
|------|------------------|-----------|----------|
| Voice(4o) | minimal | low | 응답 ≤ 2문장, 라운드트립 ≤ 600ms |
| Info(5) | medium~high | medium | 이미지·지도·표 허용, 출처 표기 필수 |
| Emergency(5+4o) | high | low | 구조화된 정보 + 4o 짧은 음성 출력 |

### 4. 멀티모달 규칙
- **이미지 입력**: GPT-5가 분석·번역 → 핵심 정보만 GPT-4o로 음성 출력 (예: 메뉴 알레르기 표시)
- **메뉴/간판**: 원문/독음/의미/알레르겐 4단계 구조화 표시 
- **지도/동선**: GPT-5가 표/리스트로 제시, GPT-4o는 1~2문장 구두 안내

### 5. 보안·프라이버시
- **데이터 처리**: 숙소/의료정보는 세션 한정 사용, 24시간 TTL 적용
- **음성 로그**: 저장 금지 (법적 요구 시 7일 보관)
- **민감정보**: "여권번호" 등 감지 시 텍스트 재확인 절차 강제

### 6. 품질지표
| 지표 | 목표치 | 측정 방법 |
|------|--------|-----------|
| Voice Latency | ≤600ms | 100회 샘플 테스트 |
| 번역 정확도 | ≥95% | 20문장 수동 검증 |
| 사실성 | ≥90% | 출처 일치율 검증 |
| 사용자 완료도 | ≥85% | 여행 단계별 이탈률 |

### 7. 테스트 시나리오
1. **알레르기 응급**: "이 메뉴 성분에 알레르기 있어요" → 이미지 업로드 → GPT-5 분석 → GPT-4o 1문장 경고 (일본어)
2. **실시간 안내**: "주유소 어디?" 음성 입력 → GPT-4o 즉답 + GPT-5가 근거 링크 테이블 생성

---

## 📅 변경 로그
- **2025-09-09 예정 변경**: Standard Voice Mode 종료, 모든 사용자 Advanced Voice Mode(GPT-4o) 통합 
- **향후 전환 대비**: GPT-5 Realtime API 출시 시 `reasoning_effort=minimal`로 음성 전환 검토
- **현재 한계**: GPT-5는 음성 처리 미지원, GPT-4o는 실시간 요구사항 충족 유일한 옵션 