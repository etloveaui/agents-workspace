# 파라미터 최적화 가이드

## 🎯 GPT5 파라미터 완전 이해

GPT5의 새로운 파라미터들(`reasoning_effort`, `verbosity`, `CFG`, `custom tools`)을 상황별로 최적화하여 비용 효율성과 성능을 동시에 확보하세요.

## ⚡ reasoning_effort 최적화 전략

### 5단계 추론 노력도 매트릭스

| Level | 사용 상황 | 예상 지연시간 | 비용 | 품질 | 최적 사례 |
|-------|-----------|--------------|------|------|-----------|
| **minimal** | 단순 작업, 빠른 응답 필요 | 최단 | 최저 | 기본 | FAQ, 간단한 번역, 형식 변환 |
| **low** | 일반적 질문, 기본 분석 | 짧음 | 낮음 | 양호 | 일반 정보 요청, 기본 요약 |
| **medium** | 균형 잡힌 작업 (기본값) | 보통 | 보통 | 좋음 | 업무 문서 작성, 중간 분석 |
| **high** | 복잡한 추론, 전문 분석 | 긺 | 높음 | 우수 | 전략 분석, 코드 리뷰, 연구 |
| **maximum** | 최고 난이도 문제 | 최장 | 최고 | 최고 | 학술 연구, 복잡한 시스템 설계 |

### 상황별 reasoning_effort 선택 가이드

#### ⚡ minimal 사용 케이스
```javascript
// API 예시
{
  "model": "gpt-5",
  "reasoning_effort": "minimal",
  "messages": [...]
}

// 최적 사용 상황
- 실시간 챗봇 응답
- 간단한 데이터 추출
- 형식 변환 (JSON ↔ CSV)
- 기본적인 번역
- 단순 분류 작업
```

**프롬프트 최적화 팁:**
- 명확하고 단순한 지시
- 복잡한 추론 요구 제거
- 즉답 가능한 질문 형태

#### 🔥 high/maximum 사용 케이스
```javascript
// 복잡한 분석이 필요한 경우
{
  "model": "gpt-5", 
  "reasoning_effort": "high",
  "verbosity": "medium",
  "messages": [...]
}

// Thinking 모드 유도 키워드
"Think deeply about this complex problem"
"Analyze all possible implications" 
"Consider multiple perspectives and alternatives"
"Provide expert-level analysis"
```

**고품질 추론 유도 전략:**
- 다단계 사고 요구
- 여러 관점 분석 요청
- 전문가 수준 기대치 명시
- 체계적 접근법 요구

## 📝 verbosity 최적화 전략

### 3단계 상세도 최적화

#### Low Verbosity (간결형)
```javascript
{
  "verbosity": "low",
  "reasoning_effort": "minimal"
}

// 최적 사용 상황
- 모바일 UI에서 짧은 답변 필요
- 대시보드용 요약 정보
- 빠른 의사결정 지원
- API 응답으로 사용할 데이터

// 출력 예시
"GPT-5의 새 기능: reasoning_effort, verbosity, CFG 지원. 성능 45% 향상, 비용 효율성 개선."
```

#### Medium Verbosity (균형형 - 기본값)
```javascript
{
  "verbosity": "medium",
  "reasoning_effort": "medium" 
}

// 최적 사용 상황  
- 일반적인 업무 문서
- 교육 콘텐츠
- 프레젠테이션 자료
- 고객 커뮤니케이션

// 출력 예시
"GPT-5는 세 가지 새로운 파라미터를 도입했습니다:
1. reasoning_effort: 추론 깊이 제어
2. verbosity: 출력 상세도 조절  
3. CFG: 구조화된 출력 보장
이를 통해 성능이 45% 향상되고 비용 효율성이 개선되었습니다."
```

#### High Verbosity (상세형)
```javascript
{
  "verbosity": "high",
  "reasoning_effort": "high"
}

// 최적 사용 상황
- 교육/학습 콘텐츠
- 상세한 분석 보고서  
- 기술 문서 작성
- 감사/검토 목적

// 출력 예시
"GPT-5는 개발자와 사용자의 세밀한 제어를 위해 세 가지 혁신적인 파라미터를 도입했습니다.

첫째, reasoning_effort 파라미터는 minimal부터 maximum까지 5단계로 모델의 추론 깊이를 제어할 수 있게 합니다. minimal은 빠른 응답이 필요한 단순 작업에, maximum은 복잡한 전문 분석에 최적화되어 있습니다.

둘째, verbosity 파라미터는 출력의 상세도를 low/medium/high로 조절하여..."
```

### verbosity 프롬프트 오버라이드

전역 verbosity 설정을 특정 상황에서만 변경하는 방법:

```markdown
# 전역: verbosity "low" 설정 상황에서

## 코딩 도구에만 high verbosity 적용
"코드 작성 시에는 상세한 주석과 설명을 포함하여 high verbosity로 작성해주세요. 
다른 응답은 간결하게 유지하세요."

## 특정 섹션만 상세하게
"다음 분석 결과는 매우 상세하게 설명해주세요: [분석 내용]
기타 섹션은 간결하게 요약해주세요."
```

## 🏗️ CFG (Context-Free Grammar) 활용

### 구조화된 출력 강제하기

#### JSON 스키마 적용
```javascript
{
  "model": "gpt-5",
  "response_format": {
    "type": "json_schema",
    "json_schema": {
      "name": "business_analysis",
      "schema": {
        "type": "object",
        "properties": {
          "summary": {
            "type": "string",
            "description": "Executive summary"
          },
          "strengths": {
            "type": "array", 
            "items": {"type": "string"}
          },
          "weaknesses": {
            "type": "array",
            "items": {"type": "string"}
          },
          "recommendations": {
            "type": "array",
            "items": {
              "type": "object",
              "properties": {
                "action": {"type": "string"},
                "priority": {"type": "string", "enum": ["high", "medium", "low"]},
                "timeline": {"type": "string"}
              }
            }
          },
          "confidence_score": {
            "type": "number",
            "minimum": 0,
            "maximum": 100
          }
        },
        "required": ["summary", "strengths", "weaknesses", "recommendations"]
      }
    }
  }
}
```

#### 코드 출력 CFG
```javascript
// 프로그래밍 언어 구문 강제
{
  "response_format": {
    "type": "cfg",
    "cfg_rules": {
      "program": "function*",
      "function": "def IDENTIFIER '(' parameters ')' ':' body",
      "parameters": "IDENTIFIER (',' IDENTIFIER)*",
      "body": "statement+",
      "statement": "assignment | return_stmt | if_stmt"
    }
  }
}
```

### CFG 최적 활용 시나리오

1. **API 응답 표준화**: 일관된 JSON 구조 보장
2. **코드 생성**: 특정 언어 문법 준수
3. **보고서 형식**: 표준 문서 구조 적용
4. **데이터 변환**: 정확한 형식 변환 보장

## 🛠️ Custom Tools 최적화

### Raw Text Payload 활용

#### Python 코드 직접 실행
```javascript
{
  "tools": [{
    "type": "custom",
    "function": {
      "name": "execute_python",
      "description": "Execute Python code directly without JSON wrapping",
      "parameters": {
        "type": "object",
        "properties": {
          "code": {
            "type": "string",
            "description": "Raw Python code to execute"
          }
        }
      }
    }
  }],
  "tool_choice": "auto"
}

// 프롬프트에서 직접 코드 전송
"다음 데이터를 분석하는 Python 코드를 작성하여 execute_python 도구로 실행해주세요:
[데이터 설명]"
```

#### SQL 쿼리 직접 실행
```javascript
{
  "tools": [{
    "type": "custom", 
    "function": {
      "name": "execute_sql",
      "description": "Execute SQL query directly",
      "parameters": {
        "type": "object",
        "properties": {
          "query": {"type": "string"},
          "database": {"type": "string"}
        }
      }
    }
  }]
}
```

## 📊 파라미터 조합 최적화 매트릭스

### 작업 유형별 최적 조합

| 작업 유형 | reasoning_effort | verbosity | CFG | 예상 비용 | 예상 품질 |
|-----------|------------------|-----------|-----|-----------|-----------|
| **FAQ 챗봇** | minimal | low | - | 💰 | ⭐⭐⭐ |
| **콘텐츠 요약** | low | medium | - | 💰💰 | ⭐⭐⭐⭐ |
| **비즈니스 분석** | high | high | JSON | 💰💰💰💰 | ⭐⭐⭐⭐⭐ |
| **코드 생성** | medium | medium | CFG | 💰💰💰 | ⭐⭐⭐⭐⭐ |
| **연구 보고서** | maximum | high | - | 💰💰💰💰💰 | ⭐⭐⭐⭐⭐ |
| **데이터 변환** | minimal | low | JSON | 💰 | ⭐⭐⭐⭐ |

### 비용 최적화 전략

#### 단계별 파라미터 조정
```javascript
// 1단계: 빠른 개요 파악 (저비용)
{
  "reasoning_effort": "minimal",
  "verbosity": "low"
}

// 2단계: 필요시 상세 분석 (고비용)  
{
  "reasoning_effort": "high",
  "verbosity": "high"
}
```

#### 배치 처리 최적화
```javascript
// 여러 단순 작업 배치
[
  {"reasoning_effort": "minimal", "task": "task1"},
  {"reasoning_effort": "minimal", "task": "task2"}, 
  {"reasoning_effort": "minimal", "task": "task3"}
]

// 복잡한 작업은 개별 처리
{"reasoning_effort": "high", "complex_analysis": "..."}
```

## 🎯 실전 최적화 팁

### Do's ✅
- **작업 복잡도에 맞는 reasoning_effort 선택**
- **출력 용도에 맞는 verbosity 설정**
- **반복 작업은 CFG로 구조화**
- **단계적 파라미터 조정으로 비용 관리**
- **프롬프트에서 명시적 품질 요구사항 제시**

### Don'ts ❌
- **항상 maximum reasoning_effort 사용**
- **불필요한 high verbosity 남용**
- **단순 작업에 복잡한 CFG 적용**
- **파라미터 조합 실험 없이 기본값만 사용**
- **비용 대비 효과 고려하지 않기**

### 성능 모니터링 지표

#### 비용 효율성
- Token usage per task
- Cost per quality unit  
- Response time vs quality tradeoff

#### 품질 지표
- Task completion accuracy
- User satisfaction score
- Output consistency rate

#### 최적화 신호
```markdown
# 파라미터 상향 조정 신호
- 답변 품질 불만족
- 복잡한 추론 필요한 작업 증가
- 전문가 수준 출력 요구

# 파라미터 하향 조정 신호  
- 비용 초과 우려
- 응답 속도 중요성 증가
- 단순 작업 비중 증가
```

## 🚀 고급 최적화 패턴

### 적응형 파라미터 조정
```markdown
# 작업 복잡도에 따른 동적 조정
IF task_complexity == "simple":
    reasoning_effort = "minimal"
    verbosity = "low"
ELIF task_complexity == "medium":
    reasoning_effort = "medium"  
    verbosity = "medium"
ELSE:  # complex
    reasoning_effort = "high"
    verbosity = "high"
```

### A/B 테스트 프레임워크
```markdown
# 파라미터 조합 성능 테스트
Version A: {reasoning_effort: "medium", verbosity: "medium"}
Version B: {reasoning_effort: "high", verbosity: "low"}

Metrics:
- Quality score
- Response time
- Cost per request
- User preference
```

이 가이드를 통해 GPT5의 파라미터를 작업 특성에 맞게 최적화하여 최고의 성능과 비용 효율성을 달성하세요!