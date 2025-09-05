# 미야코지마 여행 AI 컴패니언

**ChatGPT Projects 기반 단일 프로젝트 + 서브모드 라우팅**

## 🎯 프로젝트 개요

- **플랫폼**: ChatGPT Plus Projects (웹 기반)
- **파일 제한**: 25개 파일 업로드
- **Voice**: GPT-4o 시작 → 4o mini 폴백 (CC 자막 지원)
- **Info**: GPT-5 (텍스트/이미지/심층분석)

## 📁 파일 구조

```
/core/
├── miyakojima_guide.md     # 지역 개요·명소·매너
├── japanese_phrases.md     # 상황별 일본어
└── emergency_info.md       # 번호·기관·표현·절차

/personal/
└── personal_travel_info.md # 숙소·차량·항공·취향

/poi/
└── poi_database.csv        # POI 좌표·영업시간·평점

/route/
└── daily_routes.json       # 일별 경로 GeoJSON

/itinerary/
└── schedule.csv           # 일정표

/constraints/
└── preferences.json       # 알레르기·예산·제약사항
```

## 🚀 사용법

1. **ChatGPT Plus** 로그인
2. **Projects** → "Miyakojima Trip Assistant" 생성
3. **Instructions 탭**: `instructions/MASTER_INSTRUCTIONS.md` 업로드
4. **파일 탭**: knowledge_base/ 폴더의 모든 파일 업로드
5. **Memory**: 활성화
6. **Voice 사용 시**: CC 버튼으로 자막 확인

## ⚡ 핵심 기능

- **실시간 통역**: 음성 ↔ 일본어 (CC 자막 포함)  
- **카메라 번역**: 메뉴/간판 OCR → 알레르기 표시
- **3시간 공백 추천**: 경로 중간 POI 자동 추천
- **응급 대응**: 키워드 감지 → 구조화된 안내

---

**여행 일정**: 2025년 9월 27일 ~ 10월 1일 (4박 5일)
**목적지**: 일본 미야코지마