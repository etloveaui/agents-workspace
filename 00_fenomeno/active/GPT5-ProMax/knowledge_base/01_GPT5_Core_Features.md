# GPT5 핵심 기능 완전 가이드

## 🎯 GPT5 개요 (2025년 8월 출시)

**GPT5는 OpenAI의 가장 스마트하고 빠른 모델**로, 내장된 추론 능력과 전문가 수준의 지능을 제공합니다.

### 🏆 성능 지표
- **수학**: AIME 2025에서 94.6% (도구 없이)
- **코딩**: SWE-bench Verified 74.9%, Aider Polyglot 88%
- **멀티모달**: MMMU 84.2%
- **헬스케어**: HealthBench Hard 46.2%
- **환각 감소**: GPT-4o 대비 45% 감소, 추론 시 80% 감소

## 🤖 모델 라인업

### 1. **gpt-5** (메인 모델)
- **가격**: $1.25/1M input tokens, $10/1M output tokens
- **컨텍스트**: 272,000 tokens input, 128,000 tokens output
- **용도**: 복잡한 추론, 고품질 코딩, 전문적 분석

### 2. **gpt-5-mini** (경량 모델)
- **가격**: $0.25/1M input tokens, $2/1M output tokens
- **특징**: 빠른 응답, 비용 효율적
- **용도**: 일반적 작업, 대량 처리

### 3. **gpt-5-nano** (초경량 모델)
- **가격**: $0.05/1M input tokens, $0.40/1M output tokens
- **특징**: 최고 속도, 최저 비용
- **용도**: 단순 작업, 실시간 처리

### 4. **GPT-5 Pro** (프리미엄)
- **제공**: ChatGPT $200/월 플랜 전용
- **특징**: 최고 성능, 고급 추론

## ⚙️ 새로운 API 파라미터

### 1. **reasoning_effort** (추론 노력도)
```javascript
// 5단계 설정 가능
reasoning_effort: "minimal" | "low" | "medium" | "high" | "maximum"

// 사용 예시
{
  "model": "gpt-5",
  "reasoning_effort": "high",  // 복잡한 문제 해결 시
  "messages": [...]
}
```

**선택 가이드:**
- **minimal**: 빠른 응답 필요시, 단순 작업
- **low**: 일반적 질문, 기본 분석
- **medium**: 기본값, 균형 잡힌 성능
- **high**: 복잡한 추론, 전문적 분석
- **maximum**: 최고 난이도 문제 해결

### 2. **verbosity** (출력 상세도)
```javascript
verbosity: "low" | "medium" | "high"

// 사용 예시
{
  "model": "gpt-5",
  "verbosity": "low",     // 간결한 답변
  "messages": [...]
}
```

**출력 스타일:**
- **low**: 간결하고 핵심적인 답변
- **medium**: 균형 잡힌 상세도 (기본값)
- **high**: 매우 상세한 설명과 예시

### 3. **CFG (Context-Free Grammar)** 지원
```javascript
// 구조화된 출력 강제
{
  "model": "gpt-5",
  "response_format": {
    "type": "json_schema",
    "json_schema": {
      "name": "code_analysis",
      "schema": {
        "type": "object",
        "properties": {
          "language": {"type": "string"},
          "complexity": {"type": "string"},
          "suggestions": {"type": "array"}
        }
      }
    }
  }
}
```

### 4. **Custom Tools** (raw text payload)
```javascript
// JSON 래핑 없이 직접 텍스트 전송
{
  "type": "custom",
  "function": {
    "name": "execute_python",
    "description": "Execute Python code directly"
  }
}
```

## 🔄 Auto 모델 라우팅 시스템

GPT5는 **지능형 라우팅**으로 사용자 입력에 따라 자동으로 최적 모델 선택:

### 라우팅 기준
1. **대화 유형** 분석
2. **복잡성** 수준 평가
3. **도구 사용** 필요성
4. **명시적 의도** ("think hard about this" 등)

### 사용자 제어 옵션
- **Auto**: 자동 라우팅 (대부분 사용자 권장)
- **Fast**: 빠른 모델 강제
- **Thinking**: 추론 모델 강제

### 사용률 변화
- **추론 모델 사용**: 7% → 24% (유료 사용자)
- **무료 사용자**: 0% → 7%

## 🎨 프롬프트 최적화 전략

### 1. **모순 제거**
❌ **잘못된 예시:**
```
표준 라이브러리를 선호하되, 외부 패키지를 사용해도 됩니다.
정확한 결과를 원하지만 근사치도 괜찮습니다.
```

✅ **올바른 예시:**
```
표준 라이브러리만 사용하여 정확한 결과를 도출하세요.
```

### 2. **명확한 지침**
```
<context_gathering>
목표: 빠른 컨텍스트 수집
방법:
- 넓게 시작하여 집중된 하위 쿼리로 확장
- 병렬 쿼리 실행, 상위 히트 읽기, 중복 제거
- 과도한 검색 방지

조기 중단 기준:
- 변경할 정확한 내용 식별 가능
- 상위 히트의 70%가 하나 영역에 수렴

에스컬레이션:
- 신호 충돌 시 한 번만 정제된 배치 실행 후 진행
</context_gathering>
```

### 3. **도구 사전 설명 (Tool Preambles)**
```
<tool_preambles>
- 도구 호출 전 사용자 목표를 친근하고 명확하게 재표현
- 논리적 단계별 구조화된 계획 즉시 개요
- 파일 편집 실행 시 각 단계를 간결하고 순차적으로 설명
- 사전 계획과 구분하여 완료된 작업 요약으로 마무리
</tool_preambles>
```

## 📊 API 엔드포인트

### 1. **Responses API** (권장)
```javascript
POST https://api.openai.com/v1/responses
{
  "model": "gpt-5",
  "input": "프롬프트 입력",
  "reasoning_effort": "medium",
  "verbosity": "medium"
}
```

### 2. **Chat Completions API**
```javascript
POST https://api.openai.com/v1/chat/completions
{
  "model": "gpt-5",
  "messages": [...],
  "reasoning_effort": "medium",
  "verbosity": "medium"
}
```

## 🔧 고급 기능

### 1. **병렬 도구 호출**
- 여러 도구를 동시에 실행
- 효율성과 속도 향상

### 2. **내장 도구**
- 웹 검색
- 파일 검색  
- 이미지 생성
- 기타 유틸리티

### 3. **비용 절약 기능**
- **프롬프트 캐싱**: 반복 프롬프트 최적화
- **배치 API**: 대량 처리 비용 절감

### 4. **Structured Outputs**
- JSON 스키마 강제
- 일관된 출력 형식

## 💡 프롬프트 작성 팁

### 기본 원칙
1. **구체적이고 명확한 지시**
2. **모순 없는 일관된 요구사항**
3. **단계별 구조화된 접근**
4. **적절한 파라미터 활용**

### 예시 템플릿
```
# 목표
[구체적인 달성 목표]

# 컨텍스트
[필요한 배경 정보]

# 요구사항
- [구체적 요구사항 1]
- [구체적 요구사항 2]
- [구체적 요구사항 3]

# 출력 형식
[원하는 출력 구조]

# 제약사항
[준수해야 할 제한사항]
```

## 🎯 도메인별 활용법

### 코딩 프로젝트
```javascript
{
  "reasoning_effort": "high",
  "verbosity": "medium",
  "custom_instructions": "코드 품질 우선, 가독성 중시, 주석 포함"
}
```

### 데이터 분석
```javascript
{
  "reasoning_effort": "medium",
  "verbosity": "high",
  "response_format": "structured_analysis"
}
```

### 창작 작업
```javascript
{
  "reasoning_effort": "low",
  "verbosity": "high",
  "temperature": 0.8
}
```

이 가이드를 활용하여 GPT5의 강력한 기능을 최대한 활용하세요!