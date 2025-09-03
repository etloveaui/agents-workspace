# Codex CLI / SuperCodex 운영 요약 (정확판)

이 문서는 현재 워크스페이스에서 Codex CLI(이하 “Codex”)가 어떻게 동작하는지, 설정 우선순위, MCP 통합, 모드·프롬프트 사용법을 정확히 정리한 가이드입니다.

---

## Codex 개요

- 정의: 터미널/IDE에서 실행되는 코딩 에이전트. 이 워크스페이스에서는 “SuperCodex” 지침과 프롬프트로 확장 운용.
- 확장: MCP(Model Context Protocol) 서버와 연동하여 파일시스템, 브라우징, 문서 컨텍스트 등 기능 확장.
- 플랫폼: macOS, Linux, Windows(WSL 포함). Windows에서 WSL 셸 사용 시 드라이브는 `/mnt/c`, `/mnt/d` 등으로 접근.

---

## 설정 우선순위와 적용 범위

- Codex 설정: 프로젝트 우선 적용 → 전역 백업 적용
  - 1) `C:\Users\eunta\agents-workspace\.codex\config.toml`
  - 2) `C:\Users\eunta\.codex\config.toml`
- AGENTS 지침 우선순위(단일 소스 우선, 자동 병합 아님)
  - 1) `C:\Users\eunta\agents-workspace\AGENTS.md`
  - 2) `C:\Users\eunta\agents-workspace\.codex\AGENTS.md`
  - 3) `C:\Users\eunta\.codex\AGENTS.md`
- 런타임 우선 원칙: IDE/세션의 “시작 옵션(approval/sandbox)”이 config.toml보다 우선할 수 있음. 변경 후에는 세션 재시작 필요.

---

## 현재 워크스페이스 핵심 설정

- 승인 정책: `approval_policy = "never"`(파일 기준). 단, 세션이 `on-request`로 시작되면 승인 팝업이 발생할 수 있음.
- 샌드박스: `sandbox_mode = "workspace-write"`(파일 기준). 필요 시 `danger-full-access`로 전체 드라이브 접근 허용 가능.
- 네트워크: `network_access = true` 설정 존재.
- MCP: `.mcp.json`에 서버 다수 등록, `.codex/config.toml`에도 filesystem 등 등록(클라이언트별 사용).

승인 정책 옵션(정확)
- untrusted: 대부분 작업 승인 필요(가장 안전)
- on-request: 기본 샌드박스, 필요 시에만 승격 요청
- on-failure: 샌드박스에서 실패 시 재시도 시점에 승격
- never: 승인 없이 진행(가장 편리)

샌드박스 모드(정확)
- read-only: 읽기만 가능
- workspace-write: 워크스페이스 내 쓰기 가능, 외부는 제한
- danger-full-access: 파일시스템 제한 없음(권한 범위 내 C:/D:/J: 등 접근)

---

## MCP 통합(이 워크스페이스)

구성 파일
- `.mcp.json`(클라이언트 일반): 파일시스템, sequential-thinking, context7, playwright, serena, 그리고 커스텀 `hello-mcp` 등록됨.
- `.codex/config.toml`(Codex용): npx 기반 filesystem 등 등록 가능하며 프로젝트 설정이 전역보다 우선.

등록된 서버(주요)
- hello-mcp: 커스텀 서버(툴: echo, time). 경로 `servers/hello-mcp/index.js`.
- filesystem: 루트 `C:\Users\eunta\agents-workspace` 지정(즉시 파일 접근 가능).
- sequential-thinking: 추론 유틸.
- context7: 문서/맥락.
- playwright: 브라우저 자동화.
- serena: 다수의 코드 편집/검색 툴 제공.

검증 방법(클라이언트에서)
- tools/list로 노출 서버/툴 확인 → tools/call로 호출 확인
- filesystem: roots/list → resources/list, resources/read

---

## 모드(MODE_*.md)와 프롬프트(.codex/prompts)

모드(자동 전환 아님, 지시 시 우선 적용)
- Brainstorming, Introspection, Task_Management, Token_Efficiency

프롬프트(프로젝트 내 존재)
- 경로: `.codex/prompts/`(analyze, brainstorm, build, cleanup, design, document, estimate, explain, git, implement, improve, index, load, reflect, save, select-tool, spawn, task, test, troubleshoot, workflow 등)
- 사용: 세션에서 해당 프롬프트를 호출(에이전트에 지시하거나, 클라이언트가 제공하는 단축 명령 사용). 자동 실행되지 않음.

---

## 사용 팁(운영 정확판)

- 세션 정책 우선: `.codex/config.toml` 변경 후 적용하려면 IDE/CLI 세션 재시작.
- Windows/WSL 경로: `C:\` ↔ `/mnt/c` 매핑 유의.
- 위험 작업: `danger-full-access`는 강력하므로 의도치 않은 수정 방지를 위해 신중히 사용.

---

## 부록: 최소 동작 확인 체크리스트

- MCP 서버 기동 확인(클라이언트): tools/list, tools/call 정상
- filesystem 루트 접근: 프로젝트 파일 읽기 성공
- 프롬프트 호출: `.codex/prompts/*` 기반 템플릿 호출 정상
- 모드 지시: 요청 시 해당 모드 지침이 적용됨

이 문서는 워크스페이스의 실제 구성과 동작 기준으로 정제되었으며, 확인 불가능한 버전/릴리스 번호, 자동 병합 가설 등은 제거하거나 정확한 형태로 교정했습니다.

