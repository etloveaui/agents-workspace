# Gemini 구현 제안서: 계층적 컨텍스트 로딩 시스템

**문서 목적:** `MASTER_ARCHITECTURE_PROPOSAL.md`에 명시된 '계층적 컨텍스트 로딩' 요구사항을 Gemini 에이전트에 맞게 기술적으로 구현하는 구체적인 설계안을 제시합니다.

## 1. 목표

Gemini 에이전트가 작업을 시작할 때, 다음 3가지 소스의 컨텍스트를 순서대로 조합하여 최종 컨텍스트를 구성하도록 한다.

1.  `{project_root}/gemini.md`
2.  `{project_root}/.agent/SHARED_CONTEXT.md`
3.  `{project_root}/.gemini/gemini.md`

## 2. 제안 솔루션: '컨텍스트 준비 스크립트' 활용

Gemini CLI 자체가 여러 파일을 순차적으로 읽어 합치는 기능을 내장하고 있지 않으므로, 에이전트 실행 전에 이 작업을 대신 처리해 줄 '컨텍스트 준비 스크립트'를 도입한다.

### 2.1. 파일 구조

```
agents-workspace/
├── .agent/
│   ├── SHARED_CONTEXT.md
│   └── scripts/
│       └── prepare-context.js
├── .gemini/
│   └── gemini.md
├── gemini.md
└── package.json
```

### 2.2. 실행 흐름

1.  사용자는 `package.json`에 정의된 스크립트를 통해 Gemini를 실행한다.
    ```json
    "scripts": {
      "gemini": "node .agent/scripts/prepare-context.js gemini"
    }
    ```
    사용자는 터미널에 `npm run gemini -- "너의 임무는 무엇이니?"` 와 같이 입력한다.

2.  `prepare-context.js` 스크립트가 실행되어 다음 작업을 수행한다.
    a. **임시 컨텍스트 파일 경로 생성:** `.agent/temp/gemini_session_context.md` 와 같은 고유한 임시 파일 경로를 정한다.
    b. **컨텍스트 병합:**
        i.  `gemini.md` 파일의 내용을 읽어 임시 파일에 쓴다. (파일이 없으면 건너뛴다)
        ii. `.agent/SHARED_CONTEXT.md` 파일의 내용을 읽어 임시 파일에 추가한다.
        iii. `.gemini/gemini.md` 파일의 내용을 읽어 임시 파일에 추가한다.
    c. **Gemini CLI 실행:** 위에서 생성한 임시 파일을 `--context-file` (또는 유사한) 옵션으로 지정하여, 실제 Gemini CLI를 `child_process`로 실행한다. 사용자가 전달한 프롬프트(`"너의 임무는 무엇이니?"`)도 그대로 넘겨준다.

3.  Gemini 에이전트는 3개의 컨텍스트가 모두 합쳐진 임시 파일을 자신의 최종 지침으로 인지하고 작업을 수행한다.

4.  작업이 완료되면, `prepare-context.js` 스크립트는 생성했던 임시 파일을 삭제하여 시스템을 깨끗하게 유지한다.

## 3. 기대 효과

- Gemini 에이전트를 수정하지 않고도, 외부 스크립트를 통해 원하는 컨텍스트 로딩 방식을 완벽하게 구현할 수 있다.
- `package.json`을 통해 실행 과정을 추상화하므로, 사용자는 복잡한 내부 동작을 알 필요 없이 `npm run gemini` 명령어만 사용하면 된다.
- 다른 에이전트(Claude, Codex)에도 동일한 패턴을 적용하여 일관성 있는 시스템을 구축할 수 있다.
