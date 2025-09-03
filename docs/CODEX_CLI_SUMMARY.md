# Codex CLI - 핵심 정보 요약

이 문서는 조사한 정보를 기반으로 OpenAI Codex CLI의 주요 기능, 아키텍처, 설정 방법 및 우리가 구축한 SuperCodex 프레임워크에 대한 핵심 정보를 요약합니다.

---

## 🎯 OpenAI Codex CLI 개요

### 1. 핵심 정체성
- **출처:** https://github.com/openai/codex
- **정의:** 터미널에서 실행되는 경량 코딩 에이전트
- **버전:** v0.28.0 (최신, 2025년 9월 2일)
- **라이선스:** Apache-2.0

### 2. 주요 특징
- **로컬 실행:** 로컬 컴퓨터에서 직접 실행되는 AI 코딩 에이전트
- **다중 인증:** ChatGPT 계정 통합 (Plus, Pro, Team, Edu, Enterprise) 또는 API 키
- **샌드박스 실행:** OS 레벨 샌드박스에서 모델 생성 명령어 실행
- **MCP 지원:** Model Content Protocol을 통한 확장성
- **다중 플랫폼:** macOS, Linux, Windows(WSL2) 지원

---

## 📦 설치 및 설정

### 3. 설치 방법
```bash
# npm 전역 설치
npm install -g @openai/codex

# Homebrew 설치
brew install codex

# 바이너리 직접 다운로드 (GitHub Releases)
# https://github.com/openai/codex/releases
```

### 4. 시스템 요구사항
- **Node.js:** 22+ (LTS 권장)
- **RAM:** 4-8 GB
- **지원 OS:**
  - macOS 12+
  - Ubuntu 20.04+/Debian 10+
  - Windows 11 (WSL2 경유)

### 5. 인증 설정
- **ChatGPT 로그인:** 권장 방식 (Plus/Pro/Team/Edu/Enterprise 계정)
- **API 키:** 추가 설정 필요
- **설정 위치:** `~/.codex/config.toml`

---

## ⚙️ 핵심 설정 시스템

### 6. config.toml 구조
```toml
# 모델 설정
model = "gpt-5"
model_provider = "openai"
model_reasoning_effort = "high"
model_verbosity = "detailed"

# 보안 및 실행 정책
approval_policy = "never"     # "untrusted", "on-request", "never"
sandbox_mode = "workspace-write"  # "read-only", "workspace-write", "danger-full-access"

# 신뢰 프로젝트
[projects."path"]
trust_level = "trusted"

# MCP 서버 설정
[mcp_servers.server_name]
command = "server-command"
args = ["arg1", "arg2"]
env = { "KEY" = "value" }
```

### 7. 샌드박스 모드
- **read-only:** 파일 읽기만 가능, 쓰기/네트워크 차단
- **workspace-write:** 워크스페이스 내 쓰기 허용, 네트워크 기본 차단
- **danger-full-access:** 모든 샌드박스 제한 우회

### 8. 승인 정책
- **untrusted:** 모든 작업 승인 요청 (가장 안전하지만 번거로움)
- **on-request:** 위험한 작업만 승인 요청 (균형)
- **never:** 승인 없이 자동 실행 (가장 편리)

---

## 🎨 사용자 지정 시스템

### 9. AGENTS.md 파일 시스템
```
1. ~/.codex/AGENTS.md          # 전역 개인 가이드
2. [프로젝트루트]/AGENTS.md    # 공유 프로젝트 규칙
3. [현재폴더]/AGENTS.md        # 하위폴더/기능별 특화
```
- **처리 순서:** "top-down" 병합 (나중 파일이 이전 파일 오버라이드)
- **용도:** 지속적 프로젝트별 지침, 아키텍처 가이드라인, 코딩 규칙

### 10. 커스텀 프롬프트 시스템
```
~/.codex/prompts/
├── my-prompt.md       # /my-prompt 명령어로 사용
├── debug-helper.md    # /debug-helper 명령어로 사용
└── review-code.md     # /review-code 명령어로 사용
```
- **사용법:** 세션에서 `/` 입력 → 프롬프트 선택 → 실행
- **제한:** 새 프롬프트 추가 시 세션 재시작 필요

---

## 🔧 MCP (Model Content Protocol) 통합

### 11. MCP 서버 생태계
- **Filesystem:** 파일 시스템 접근
- **Sequential Thinking:** 구조화된 다단계 추론
- **Context7:** 문서화 및 컨텍스트 관리
- **Custom Servers:** 프로젝트별 특화 도구

### 12. MCP 설정 예제
```toml
[mcp_servers.filesystem]
command = "mcp-server-filesystem"
args = ["/project/path"]

[mcp_servers.sequential]
command = "mcp-server-sequential-thinking"

[mcp_servers.context7]
command = "npx"
args = ["-y", "@modelcontextprotocol/server-context7"]
```

---

## 🎯 VS Code 통합

### 13. IDE Extension
- **이름:** "Codex — OpenAI's coding agent"
- **플랫폼:** macOS, Linux, Windows (실험적)
- **요구사항:** ChatGPT Plus/Pro/Team/Enterprise 계정
- **기능:**
  - VS Code 패널에서 채팅, 편집, 미리보기
  - 열린 파일과 선택된 코드의 컨텍스트 활용
  - 실시간 코드 수정 및 테스트 실행

### 14. 설치 방법
1. VS Code Extensions에서 "Codex" 검색
2. "Codex — OpenAI's coding agent" 설치
3. ChatGPT 계정으로 로그인
4. 로컬/클라우드 환경 선택

---

## 🚀 SuperCodex 프레임워크

### 15. SuperCodex 개요
우리가 구축한 향상된 Codex 프레임워크로, Claude SuperClaude와 Gemini SuperGemini에서 영감을 받아 설계되었습니다.

### 16. 구축된 구성요소

#### **AGENTS.md 시스템**
```
C:\Users\eunta\.codex\AGENTS.md
```
- SuperCodex 핵심 지침과 원칙
- 소프트웨어 엔지니어링 원칙 (SOLID, DRY, KISS, YAGNI)
- 워크플로우 규칙 및 품질 표준
- Git 워크플로우 및 보안 규칙
- 전문적 표준 및 범위 규율

#### **커스텀 프롬프트 라이브러리**
```
C:\Users\eunta\.codex\prompts\
├── analyze.md      # /analyze - 다영역 코드 분석
├── implement.md    # /implement - 프로덕션 품질 구현
├── debug.md        # /debug - 체계적 문제 해결
├── optimize.md     # /optimize - 안전한 코드 개선
└── document.md     # /document - 포괄적 기술 문서화
```

#### **MCP 서버 통합**
```toml
[mcp_servers.filesystem]
command = "mcp-server-filesystem"
args = ["C:\\Users\\eunta\\agents-workspace"]

[mcp_servers.sequential]
command = "mcp-server-sequential-thinking"
```

#### **프로파일 기반 MODE 시스템**
```toml
[profiles.analysis]        # 분석 모드: 높은 추론력, 상세한 출력
[profiles.implementation]  # 구현 모드: 중간 추론력, 일반 출력
[profiles.debug]          # 디버그 모드: 높은 추론력, 상세한 출력
[profiles.optimize]       # 최적화 모드: 중간 추론력, 일반 출력
```

### 17. SuperCodex 사용법

#### **기본 실행**
```bash
codex                    # 기본 대화형 모드
codex --profile analysis # 분석 모드로 실행
codex --profile debug    # 디버그 모드로 실행
```

#### **커스텀 프롬프트 사용**
```bash
# Codex 세션 내에서
/analyze     # 품질, 보안, 성능, 아키텍처 분석
/implement   # 프로덕션 품질 기능 구현
/debug       # 체계적 문제 진단 및 해결
/optimize    # 안전한 코드 개선 및 최적화
/document    # 포괄적 기술 문서 작성
```

### 18. SuperCodex 핵심 원칙
- **Evidence > assumptions | Code > documentation | Efficiency > verbosity**
- **Task-First Approach:** Understand → Plan → Execute → Validate
- **Quality Standards:** Critical → Important → Recommended 우선순위
- **No Partial Features:** 시작하면 완료까지
- **Professional Honesty:** 증거 기반 평가, 마케팅 언어 금지

---

## 🔄 최적화된 설정

### 19. 권한 및 신뢰 설정
```toml
# 최적화된 권한 설정
approval_policy = "never"
sandbox_mode = "workspace-write"

[sandbox_workspace_write]
network_access = true

# 신뢰 프로젝트
[projects."C:\\Users\\eunta\\agents-workspace"]
trust_level = "trusted"
```

### 20. 성능 최적화
- **모델:** gpt-5 (최신 모델 사용)
- **추론 강도:** 프로파일별 차등 적용
- **출력 상세도:** 작업 유형에 따라 조절
- **MCP 서버:** 필요한 서버만 선택적 활성화

---

## 📊 비교: 기본 Codex vs SuperCodex

| 기능 | 기본 Codex | SuperCodex |
|------|------------|------------|
| 기본 지침 | 하드코딩된 시스템 프롬프트 | AGENTS.md 커스터마이징 |
| 명령어 시스템 | 기본 명령어만 | 5개 커스텀 프롬프트 |
| 모드 전환 | 단일 설정 | 4개 프로파일 시스템 |
| MCP 통합 | 기본적 | Sequential + 확장 |
| 품질 표준 | 기본적 | 체계적 엔지니어링 원칙 |
| 워크플로우 | 즉흥적 | 구조화된 패턴 |

---

## 💡 향후 확장 계획

### 21. 단기 계획
- 추가 MCP 서버 통합 (Context7, 특화 도구들)
- 프로젝트별 AGENTS.md 템플릿
- 더 많은 커스텀 프롬프트 추가

### 22. 장기 비전
- Codex-Gemini-Claude 상호 운용성
- 통합 에이전트 워크스페이스 구축
- AI 도구들 간의 지능적 작업 분배

---

**결론:** SuperCodex는 기본 Codex CLI의 강력함에 체계적 엔지니어링 원칙과 커스터마이징을 더해, Claude SuperClaude와 동등한 수준의 지능적 코딩 에이전트로 진화시킨 프레임워크입니다.