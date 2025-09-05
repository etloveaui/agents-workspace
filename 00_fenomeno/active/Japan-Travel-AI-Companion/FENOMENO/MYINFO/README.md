내 정보들을 모아서 제공하는 곳. 이곳의 자료들을 잘 정리해서 knowleage_base 쪽에 잘 작성해서 놓고 지침에도 반영하도록 한다.
언제 새로운 파일들이 들어올지 모르니 새로운 파일이 생기면 확인하고 모르거나 아리까리하면 나한테 꼭 물어본다.
추가적으로 필요한 자료가 있다면 요청하고 이곳에서 가져간다.





20250905-17:48: New Info 지식파일의 구조를 다시 바꿔야. 한다. 음성 대화의 경우 CSV 접근이 쉽지 않다고 한다. 아래는 GPT의 답변, 따라서 md, json, txt로 최대한 지식파을을 맞춰서 작성해야한다. 

음성 모드에서도 접근되는 건 내가 **이미 불러온 지식파일(md, json, txt 등 텍스트 기반)**이다.
CSV, Excel 같은 구조화된 파일은 음성 모드에선 직접 열 수 없고, 텍스트 모드에서만 처리된다.
정리:
음성 모드 접근 가능: .md, .txt, .json 같은 텍스트 지식파일.
텍스트 모드 필요: .csv, .xlsx, .ods 같은 표 데이터 파일.
CSV 내용도 음성 중에 활용하고 싶다면, 먼저 텍스트 모드에서 필요한 부분을 뽑아 요약 지식으로 변환해 두는 방식이 효율적이다.
지금 CSV를 요약본(md/json)으로 만들어둘까?

20250905-17:50: 추가요청 사항 현재 지식파일에 니가 필수로 필요하다고 말한 파일외에 파일들이 많이 있다. 필요없어진 파일들은 헷깔리지 않게 아카이브나 다른곳으로 미리미리 이동시켜주길 바란다. 아래는 니가 한 답변

> ㅇㅋ 내가 프로젝트에 어떻게 구성하면 되는지 간략히 알려줄래?

● 🚀 ChatGPT Projects 설정 가이드

  📁 업로드할 파일들 (우선순위순)

  1️⃣ 필수 파일

  instructions/MASTER_INSTRUCTIONS.md          # 메인 지침서
  data/confirmed_schedule.csv                 # 확정 일정 (항공/숙소)
  data/constraints.json                       # 개인정보 (여권/예약번호)
  knowledge_base/accommodation_strategy.md     # 숙소별 전략

  2️⃣ 활동 관련

  data/suggested_activities.csv               # 제안 활동들
  data/booking_todo.csv                       # 예약할 것들
  data/poi_database.csv                       # 장소 데이터

  3️⃣ 여행 정보

  knowledge_base/miyakojima_guide.md          # 미야코지마 가이드
  knowledge_base/japanese_phrases.md          # 일본어 표현
  knowledge_base/emergency_info.md            # 응급정보

  ⚙️ ChatGPT Projects 설정

  1. 새 프로젝트 생성: "미야코지마 여행 AI"
  2. Instructions: MASTER_INSTRUCTIONS.md 내용 복붙
  3. Knowledge: 위 파일들 업로드 (25개 제한)
  4. 모델: GPT-4o (Voice) + GPT-5 (Text/Image)

  🎯 사용법

  음성: "이거 일본어로 뭐라고 해?" → 즉시 번역텍스트: "힐튼에서 뭐 할까?" → 확정/제안 구분해서       
  답변이미지: 메뉴판 사진 → 번역 + 개인 취향 맞춤 추천

  🔥 핵심: 확정된 건 못 바꾸고, 제안된 건 조정 가능하다고 명확히 구분해서 답변함

> c:\Users\eunta\agents-workspace\00_fenomeno\active\Japan-Travel-AI-Companion\FENOMENO\MYINFO\정보  
  .md 정보 좀더 업데이트 했어. 확인하고 그거에 맞게 업데이트 해줘

● Read(00_fenomeno\active\Japan-Travel-AI-Companion\FENOMENO\MYINFO\정보.md)
  ⎿  Read 69 lines (ctrl+r to expand)
  ⎿  5-hour limit reached ∙ resets 9pm
     /upgrade to increase your usage limit.