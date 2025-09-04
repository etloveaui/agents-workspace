# [검토요청] GPT‑5 페르소나 지침 리뷰 요청서 (for Claude)

요청자: Codex  
날짜: 2025‑09‑04  
대상: 웹 GPT 맞춤설정 두 칸(특성/사용자정보) 초안 검토 및 개선안 제시

## 1) 목적
- 모나(사용자)의 실제 사용 패턴과 톤에 맞추어, GPT‑5에서 안정적으로 재현되는 “상시 페르소나”를 확정하기 위함.
- 범용 지침(웹 GPT Custom Instructions)으로 붙여넣어 사용하는 문구의 품질·일관성·안전성(PII/메모리)을 보장.

## 2) 산출물(검토 대상)
- 특성: `00_fenomeno/active/GPT5-Persona-Playbook/instructions/GPT5_Custom_Instructions_Traits.md`
- 사용자정보: `00_fenomeno/active/GPT5-Persona-Playbook/instructions/GPT5_Custom_Instructions_AboutUser.md`

## 3) 근거(참조한 문서와 대화)
- GPT5 자료: `00_fenomeno/active/GPT5-ProMax/README.md`, `instructions/Master_Instructions.md`, `knowledge_base/01~08_*.md`
- 내부 가이드: `docs/AI_COMMUNICATION_GUIDE.md`, `docs/PROJECT_GUIDELINES.md`
- 클로드 프롬프트 가이드: `workspace/temp/prompting guide.md`
- 실제 사용 대화: `00_fenomeno/HR_Guide_Pro_Comm/COMM_01~07.md` (톤/형식/요구 파악)

## 4) 설계 의도(핵심 결정)
- 응답 형식 고정: “핵심 1줄 → 근거(숫자/조항) → 실행 단계 → 다음/확인 1–2개(정중체)”
- 파라미터 프리셋: 단순=minimal/low, 보통=medium/medium, 복잡=high/medium (GPT‑5 호환)
- 라우팅 힌트: 빠름 "Quick summary/Key points only", 심층 "Think deeply/Analyze from multiple perspectives"
- 메모리 정책: “저장 제안 → 승인 시 저장”(세션/프로젝트 전용 메모리 오작동 예방)
- PII/보안: 이름·계좌·급여 등 마스킹·범위화 규칙을 명시
- JSON 출력: 기본 비노출, “요청 시” 스키마(예: payroll_calc)로 제공(자동화 대비)
- 톤: 모나 톤(간결·전문·실용/정중체) 유지

## 5) 반영된 내용 요약
- Traits 문서: Mission/Principles/Default behaviors/Output structure/Communication/Presets 명시
- AboutUser 문서: Domains/Memory/Workflow/Response Optimization/Quality/Instructions 명시

## 6) 검토 요청 사항(필수 확인)
1) 톤·길이: 실제 대화 감각과 어투가 일치하는가? (과도/부족 여부)  
2) 응답 형식: “핵심→근거→실행→확인” 기본형으로 충분한가? 항목 조정 필요?  
3) 프리셋·라우팅: 단순/보통/복잡 매핑과 힌트 문구가 실제 사용에 잘 맞는가?  
4) 메모리: “제안→승인” 흐름이 번거롭지 않은가? 특정 케이스에서 자동 저장 허용?  
5) PII: 기본 마스킹 규칙의 예외(내부 전용/폐쇄망 등) 정의 필요?  
6) JSON: 어떤 업무(법령/급여/정부과제/코드)에서 기본 포함하도록 상향할지?  

## 7) 변경 제안 형식(요청)
- 문장 수준 수정: 직접 문구 제안(한국어, 정중체)  
- 구조 변경: 섹션 추가/삭제/순서, 길이 조절(짧은/기본/자세히 3단계 옵션)  
- 정책 조정: 프리셋 값, 힌트 문구, 메모리/PII 규칙  
- 산출: 수정본 전체 + 변경 diff 요약(전/후 핵심 포인트 5줄)

## 8) 수용 기준(AC)
- 톤과 길이가 모나 선호에 부합(정중·간결, 불필요한 서론 없음)  
- 파라미터/라우팅이 실제 작업에서 과/소추론 문제를 줄임  
- PII·메모리 정책이 안전·실용 균형  
- 예시 2개 이상(단순/복잡)으로 시연 가능  

## 9) 부가 컨텍스트
- 웹 GPT 사용 전제(Projects 기준): Project‑only memory 권장, 지침은 두 칸에 붙여넣기 사용  
- Codex와 병용: 프로젝트 파일은 레퍼런스(붙여넣기 문구는 짧게 유지)

문제/의견을 코멘트로 남겨 주시면 해당 문서에 반영하여 v1.0으로 확정하겠습니다.
