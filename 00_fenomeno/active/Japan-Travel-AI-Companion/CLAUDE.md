# 미야코지마 여행 AI 컴패니언 - 프로젝트 개요

## 🎯 프로젝트 정보
- **여행자**: 김은태님 & 여자친구  
- **일정**: 2025년 9월 27일 ~ 10월 1일 (4박 5일)
- **플랫폼**: ChatGPT Projects (GPT-5 + Voice)
- **목표**: 언어 장벽 없는 완벽한 일본 여행

## 📁 파일 구조 (단순화)

```
Japan-Travel-AI-Companion/
├── instructions/MASTER_INSTRUCTIONS.md    # ChatGPT Projects 메인 지침
├── knowledge_base/                         # 여행 정보
│   ├── personal_travel_info.md            # 개인 여행 정보
│   ├── miyakojima_guide.md               # 미야코지마 가이드
│   ├── japanese_phrases.md               # 일본어 표현집
│   └── emergency_info.md                 # 응급상황 정보
├── data/                                  # 데이터 파일
│   ├── poi_database.csv                   # POI 좌표 데이터
│   └── route_plans.json                  # 추천 경로 데이터
├── SETUP.md                              # 설정 가이드
└── README.md                             # 프로젝트 소개
```

## 🚀 핵심 기능

### 실시간 통역 (Voice Mode - GPT-4o)
- 한↔일 즉시 번역 (<600ms)
- 발음 가이드 포함
- 응급 키워드 자동 감지

### 상세 분석 (Text/Image Mode - GPT-5) 
- 메뉴판, 간판 정확한 번역
- 개인정보 기반 맞춤 추천
- 동선 최적화 및 예산 고려

### 응급상황 대응
- "아파", "도움" 등 키워드 감지
- 병원/경찰서 위치 즉시 제공
- 필요한 일본어 표현 제공

## 🎯 사용 시나리오

### 일상 대화
- **음성**: "이거 뭐예요?" → 즉시 일본어 번역
- **이미지**: 메뉴판 사진 → 전체 번역 + 추천도

### 여행 계획
- **텍스트**: "맛집 추천해줘" → 개인 선호도 기반 추천
- **위치**: 현재 위치 → 근처 관광지 + 교통편

### 응급상황
- **음성**: "아파요" → 자동 high reasoning 모드
- **즉시**: 병원 위치 + 교통편 + 응급 표현

## ⚙️ ChatGPT Projects 설정

**업로드 파일:**
1. Instructions: `MASTER_INSTRUCTIONS.md`
2. Knowledge: `knowledge_base/` 전체 + `data/` 파일들

**모델 설정:**
- GPT-5 (텍스트/이미지 분석)
- Voice Mode 활성화 (GPT-4o 엔진)
- Vision Mode 활성화

---

**📌 이 프로젝트는 단순하고 실용적인 ChatGPT Projects 기반 여행 도우미입니다.**