다음 프롬프트를 그대로 넣어 실행하면 된다. 목적: **최근 모델 기준의 실제 사용자 사례**를 수집·검증하고, **\[MN\&FK] Travel AI**에 이식 가능한 인사이트를 도출한다. 출력은 한국어.

---

# \[DEEP RESEARCH] 여행·통역·멀티모달 실제 사용사례 수집/검증

## 🎯 Research Mission

1. **실제 사용자 사례**를 최신 버전(2025-08\~09) 기준으로 수집한다.
2. **음성+카메라 동시 사용**, **CC(자막·독음) 통역 흐름**, **경로 중 ‘공백 시간’ 추천**의 **구체적 워크플로우**와 **성공/한계**를 파악한다.
3. 결과를 **\[MN\&FK] Travel AI** 지침/지식베이스에 바로 이식 가능한 형태로 정리한다.

## 🗓 Recency Window

* 1차: 2025-08-01 \~ 2025-09-10
* 과거 자료 인용 시 최신 공지/도큐와 **충돌 여부** 교차검증 필수

## 🔎 Source Priority (순서 고정)

1. **OpenAI 공식**: 제품 페이지, Help Center(Voice/CC), Realtime/Audio 문서
2. **OpenAI Cookbook**: Voice, Realtime, 4o/5 모델 데모·코드
3. **대형 매체/공식 블로그**: The Verge, TechRadar, Wired, Nikkei 등
4. **커뮤니티/실사용**: Reddit(r/ChatGPT, r/JapanTravel), YouTube·TikTok 여행 브이로그, X 스레드, 블로그 후기
5. **지도/여행 플랫폼**: Google Maps 커뮤니티 포스트, TripAdvisor, NAVITIME, Jalan

## 🔍 Concrete Queries (다국어 병렬)

* 한국어: “ChatGPT 음성 자막 CC 사용법 여행”, “여행 중 카메라 번역 실제 사용”, “일본 여행 통역 실사용 후기 GPT”
* 영어: “ChatGPT Voice + camera live travel demo”, “real-world travel translator workflow”, “CC subtitles pronunciation ChatGPT”
* 일본어: “ChatGPT 音声 字幕 使い方 旅行”, “カメラ翻訳 実例 Miyakojima”, “経路 途中 立ち寄り おすすめ 事例”
* 기술: “OpenAI Cookbook voice realtime”, “gpt-4o chatgpt voice cc”, “route itinerary stopover recommendations case study”

## 📥 Evidence Capture Rules

* 각 사례마다 **짧은 인용(≤25단어)** + **링크** + **접근일(YYYY-MM-DD)**
* 앱/OS/버전·모델명(Voice=4o 여부) 명시
* 시연 영상은 **타임스탬프** 포함

## 🧱 Case Card 스키마(반드시 채워라)

```json
{
  "case_id": "",
  "use_case": "통역_CC | 카메라번역 | 음성+카메라 동시 | 경로_공백추천 | 기타",
  "context": { "country": "", "city": "", "language_pair": "KO↔JA/EN↔JA", "network": "4G/5G/Wi-Fi" },
  "device_app": { "device": "", "os_ver": "", "app_ver": "", "headset": "AirPods/유선/없음" },
  "model_engine": { "voice_engine": "gpt-4o?", "text_image": "gpt-5?" },
  "steps": ["", "", ""],
  "outputs": { "voice": "유/무", "cc": "유/무", "screen": "표/리스트/지도" },
  "metrics": { "latency_ms": 0, "success_rate": "", "typo_rate": "", "user_effort": "낮음/보통/높음" },
  "pain_points": ["마이크 인식", "소음", "발음", "명령어 혼동", "지도 전환 지연"],
  "workarounds": ["짧은 문장 사용", "재낭독", "키워드 트리거"],
  "evidence": [{ "quote": "", "url": "", "date": "" }],
  "transfer_to_MNFK": ["지침 반영점 1", "UI/흐름 개선점 1"]
}
```

## 📊 Extraction Tables (필수 산출)

1. **Evidence Matrix**: 출처/링크/요지/날짜/모델·버전
2. **Feature–Use Map**: 기능(Voice CC, 카메라, 경로 추천) ↔ 실제 사용 단계
3. **Failure→대응 매핑**: 실패 유형 ↔ 해결/우회
4. **Adoption Patterns**: 어떤 설정과 습관이 성공률을 높였는가

## 🧠 Analysis Tasks

* **T1. CC 통역 플로우 실제 패턴**

  * 한국어 입력 → JA 음성 출력 + **화면 3행**(JA 원문/한국어 독음/한국어 뜻) 동시 표출 사례
  * 성공 조건: 문장 길이, 억양, 주변 소음, 재낭독 명령어
* **T2. 음성+카메라 동시 사용**

  * 사진 업로드 타이밍, 안내 한/두 문장 요약, 화면 표 병행 사례
  * 메뉴/간판 번역 시 **알레르겐/주의** 라벨링 실전 예
* **T3. 경로 중 2\~4시간 ‘공백 추천’**

  * 실제 드라이브/도보 중간 들림 사례: 지도/리뷰 근거, 우회시간 임계치, 오픈시간 필터
  * 성공 UX: 추천 수(≤5), 사유 1줄, 내비 연동
* **T4. 장치/네트워크 요인**

  * 헤드셋·마이크·네트워크 품질이 성공률에 미치는 영향 정리
* **T5. 모델/버전 확인**

  * ChatGPT Voice=4o, 텍스트·이미지=5 사용 표기 여부와 실 사용자 인식 차이

## 🧩 Synthesis → \[MN\&FK] 적용 가이드

* **지침 업데이트 제안**: 통역 톤 전환(공손/캐주얼), 재낭독 핫키, 길이 가이드
* **지식베이스 추가**: 자주 쓰는 명령 템플릿, 알레르겐 표 스니펫, 경로추천 스코어 규칙
* **데이터 요구**: POI CSV, Route GeoJSON, Itinerary CSV, Constraints JSON의 **필수 필드**와 수집 팁
* **테스트 시나리오**: 케이스카드 Top 10을 리그레션 테스트로 편성

## 🚦 Adjudication Rules

* 충돌 시 **공식 문서 > Cookbook > 대형 매체 > 커뮤니티** 우선
* 링크 불명/버전 불명 사례는 **참고용**으로만 분리 표기
* 결론에는 **신뢰도(0\~1)** 부여

## 🧾 Deliverables

1. **Executive Summary** 10줄
2. **Evidence Matrix** 표
3. **Case Cards** 최소 15건(JSON+표 동시)
4. **적용 가이드 v1.0**: 지침 반영안, 지식 추가안, 테스트 10케이스
5. **Open Questions**: 추후 검증 과제 목록

## ⚙️ Model Settings (권장)

* 조사/검증 단계: `reasoning_effort=high`, `verbosity=medium`
* 정리/작성 단계: `reasoning_effort=medium`, `verbosity=medium`

## 🗣️ Command Hints (실사용 문구 수집용)

* “더 공손하게/더 캐주얼하게 말해줘”
* “한 줄로 다시 말해줘 / 재낭독”
* “카메라 번역하고 핵심만 소리로 알려줘”
* “A→B 가는 길 3시간 비어. 경로에서 들를 곳 3개만”

---

이 프롬프트로 수집된 사례를 주면, 내가 **지침 업데이트**와 **스키마화**까지 바로 이어서 처리한다.
