# Gemini CLI - 핵심 정보 요약

이 문서는 제공된 URL을 기반으로 Gemini CLI의 주요 기능, 아키텍처, 개발 및 기여 방법에 대한 핵심 정보를 요약합니다.

---

### 1. README.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/README.md
- **핵심 정체성:** Gemini 1.5 Pro의 강력한 기능을 터미널로 가져오는 오픈소스 AI 에이전트입니다.
- **주요 특징:**
    - 넉넉한 무료 등급 (분당 60개 요청).
    - 1M 토큰의 대규모 컨텍스트 창.
    - Google 검색, 파일 작업, 셸 명령, 웹 가져오기 등 내장 도구.
    - MCP(Model Context Protocol)를 통한 확장성.
    - CI/CD 통합을 위한 공식 GitHub Action.
- **설치:**
    - `npx`를 통한 설치 없는 즉시 실행.
    - `npm` (`@google/gemini-cli`) 또는 `Homebrew` (`gemini-cli`)를 통한 전역 설치.
    - Node.js 20 이상 필요.
- **인증:**
    - OAuth 로그인 (개인 개발자에게 권장).
    - Gemini API 키.
    - Vertex AI (엔터프라이즈용).
- **기본 사용법:**
    - `gemini`: 대화형 세션을 시작합니다.
    - `gemini -p "..."`: 비대화형으로 실행합니다.
    - `gemini > ...`: 프롬프트로 새 프로젝트를 시작합니다.

---

### 2. GEMINI.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/GEMINI.md
- **개발 철학:**
    - **유효성 검사:** 제출 전 `npm run preflight`를 사용하여 모든 검사(빌드, 테스트, 타입 체크, 린트)를 실행해야 합니다.
    - **테스트 (Vitest):** 테스트 파일은 소스 파일과 함께 위치하며(`*.test.ts`), `vi.mock()`을 광범위하게 사용합니다.
    - **코딩 스타일 (JS/TS):**
        - 클래스보다 일반 객체(Plain Objects)를 선호합니다.
        - 캡슐화를 위해 ES 모듈(`import`/`export`)을 사용합니다.
        - `any` 타입 사용을 지양하고, `unknown` 타입을 선호합니다.
        - 타입 단언(`as`)은 신중하게 사용합니다.
    - **React 스타일 (Ink 기반 CLI UI):**
        - 함수형 컴포넌트와 훅을 사용합니다.
        - 상태는 불변적으로 업데이트합니다.
        - `useEffect`는 외부 상태와의 동기화를 위해 최소한으로 사용합니다.
        - `useMemo`, `useCallback` 등의 수동 최적화 대신 React Compiler에 의존합니다.
    - **주석:** 가치가 높은 주석만 작성합니다.
    - **플래그 이름:** 밑줄(`_`) 대신 하이픈(`-`)을 사용합니다 (예: `my-flag`).

---

### 3. CONTRIBUTING.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/CONTRIBUTING.md
- **기여 절차:**
    - **CLA:** 기여자 라이선스 계약(Contributor License Agreement)에 서명해야 합니다.
    - **PR:** 모든 제출물은 GitHub PR을 통해 검토됩니다.
    - **이슈:** `/assign` 명령어로 이슈를 자신에게 할당할 수 있습니다 (최대 3개).
- **PR 가이드라인:**
    - 기존 이슈에 연결합니다.
    - 작고 집중된 단위로 유지합니다.
    - 진행 중인 작업은 Draft PR을 사용합니다.
    - 모든 자동화된 검사(`npm run preflight`)를 통과해야 합니다.
    - 사용자 대상 변경 시 문서를 업데이트합니다.
- **개발 설정:**
    - Node.js `~20.19.0` 버전이 필요합니다.
    - `npm install` -> `npm run build` -> `npm start` 순으로 실행합니다.
- **테스트 및 디버깅:**
    - `npm run test` (단위 테스트), `npm run test:e2e` (통합 테스트).
    - `npm run debug`와 VS Code의 디버거를 연결하여 디버깅합니다.
    - React DevTools를 사용하여 UI를 디버깅할 수 있습니다.

---

### 4. ROADMAP.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/ROADMAP.md
- **공식 로드맵:** GitHub 프로젝트에서 실시간으로 관리됩니다: [Official Roadmap](https://github.com/orgs/google-gemini/projects/11/)
- **핵심 원칙:**
    - **강력함 & 단순함:** 최첨단 모델을 가볍고 직관적인 CLI로 제공.
    - **확장성:** 다양한 사용 사례에 적응 가능한 에이전트.
    - **지능:** 최고의 에이전트 도구를 목표.
    - **무료 & 오픈소스:** 활발한 커뮤니티를 지향.
- **주요 집중 분야:**
    - 인증, 모델 지원(멀티모달 등), 사용자 경험, 도구(MCP), 확장성(GitHub 등), 백그라운드 에이전트, 보안.
- **기여 방법:** 로드맵과 연계된 기여를 우선적으로 처리하며, 버그 리포트, 기능 제안, 코드 기여, 문서 작성 등을 환영합니다.

---

### 5. docs/architecture.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/docs/architecture.md
- **핵심 컴포넌트:**
    1.  **CLI 패키지 (`packages/cli`):** 사용자 인터페이스(프론트엔드). 입력 처리, 출력 렌더링, UI 커스터마이징 담당.
    2.  **Core 패키지 (`packages/core`):** 백엔드. Gemini API와 통신, 프롬프트 관리, 도구 실행 오케스트레이션 담당.
    3.  **도구 (`packages/core/src/tools/`):** 파일 시스템, 셸, 웹 등 로컬 환경과 상호작용하는 모듈.
- **상호작용 흐름:**
    - `cli` (입력) → `core` (프롬프트 구성) → Gemini API → `core` (도구 실행, 필요시 사용자 확인) → Gemini API (최종 응답 생성) → `core` → `cli` (출력).
- **설계 원칙:** 모듈성, 확장성, 사용자 경험.

---

### 6. docs/tools/mcp-server.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/docs/tools/mcp-server.md
- **MCP 서버란?:** 외부 시스템(DB, API 등)과 상호작용하는 도구를 CLI에 노출하는 애플리케이션.
- **설정 (`settings.json`):**
    - `mcpServers` 객체에 서버를 정의합니다.
    - `command` (Stdio), `url` (SSE), `httpUrl` (HTTP) 전송 방식을 지원합니다.
    - `trust: true` 설정 시 해당 서버의 모든 도구 사용 확인을 건너뜁니다.
- **OAuth 2.0 지원:** 원격 MCP 서버에 대한 보안 인증을 지원하며, 자동 검색 및 토큰 관리가 가능합니다.
- **상호작용:**
    - `/mcp` 명령어로 설정된 서버의 상태와 사용 가능한 도구를 확인합니다.
    - `gemini mcp add/list/remove` 명령어로 서버 설정을 관리합니다.
- **고급 기능:**
    - **리치 콘텐츠:** 도구는 텍스트, 이미지 등 여러 종류의 데이터를 하나의 응답으로 반환할 수 있습니다.
    - **슬래시 명령어:** 서버에 사전 정의된 프롬프트를 CLI에서 슬래시 명령어로 쉽게 실행할 수 있습니다.

---

### 7. docs/ide-integration.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/docs/ide-integration.md
- **지원 IDE:** Visual Studio Code (및 해당 확장 프로그램을 지원하는 에디터).
- **주요 기능:**
    - **워크스페이스 컨텍스트:** 최근 파일 10개, 커서 위치, 선택된 텍스트를 자동으로 인식하여 더 정확한 응답 제공.
    - **네이티브 Diff 뷰어:** 코드 수정 제안을 IDE의 Diff 뷰어에서 직접 검토하고 수정/적용 가능.
    - **VS Code 명령어:** `Gemini CLI: Run`, `Gemini CLI: Accept Diff` 등 명령어 팔레트에서 직접 실행.
- **설정 및 사용:**
    - CLI 내에서 `/ide install` 또는 자동 설치 제안을 통해 "Gemini CLI Companion" 확장 프로그램을 설치합니다.
    - `/ide enable|disable|status` 명령어로 연결을 제어하고 상태를 확인합니다.

---

### 8. docs/sandbox.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/docs/sandbox.md
- **목적:** 잠재적으로 위험한 작업(셸 명령, 파일 수정)을 호스트 시스템으로부터 격리하여 보안을 강화합니다.
- **방식:**
    1.  **macOS Seatbelt:** macOS 내장 샌드박싱.
    2.  **컨테이너 기반 (Docker/Podman):** 완벽한 프로세스 격리를 제공하는 크로스플랫폼 방식.
- **활성화 방법:**
    - 명령어 플래그: `-s` 또는 `--sandbox`.
    - 환경 변수: `GEMINI_SANDBOX=true`.
    - `settings.json` 파일 설정.
- **보안:** 샌드박싱은 위험을 줄여주지만 완전히 제거하지는 않으므로, 가능한 가장 제한적인 프로필을 사용하는 것이 좋습니다.

---

### 9. docs/extension.md
- **출처:** https://github.com/google-gemini/gemini-cli/blob/main/docs/extension.md
- **작동 방식:**
    - 시작 시 `~/.gemini/extensions`와 `<workspace>/.gemini/extensions` 디렉토리에서 확장을 로드합니다.
    - 각 확장 디렉토리에는 `gemini-extension.json` 설정 파일이 있습니다.
- **`gemini-extension.json`:**
    - 확장 이름, 버전, MCP 서버 설정, 컨텍스트 파일 이름, 제외할 도구 등을 정의합니다.
- **확장 기능:**
    - **MCP 서버 추가:** 확장을 통해 새로운 MCP 서버를 동적으로 추가할 수 있습니다.
    - **사용자 정의 명령어:** 확장 디렉토리 내 `commands/`에 TOML 파일을 배치하여 새로운 슬래시 명령어를 추가할 수 있습니다.
- **설치:** `gemini extensions install <git_url_or_local_path>` 명령어로 설치합니다.
