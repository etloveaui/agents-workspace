# GPT-5 + Voice 통합 프로젝트 지침서 v1.0
## 여행 전용 AI 시스템 설계

### 🎯 프로젝트 개요

**검증된 사실 기반 전제:**
- **텍스트/이미지 처리**: GPT-5 (2025-08-07 출시)
- **실시간 음성 처리**: GPT-4o (ChatGPT Voice, 2025-09-09 통합 완료)
- **라우팅 방식**: 입력 모달리티별 자동 분기

---

## 📊 1. 아키텍처 개요

### 1.1 단일 프로젝트 + 서브모드 라우팅

```
사용자 입력
    ↓
[입력 유형 감지]
    ↓
┌─────────────────────┐    ┌─────────────────────┐
│   텍스트/이미지     │    │    음성 입력        │
│   → GPT-5          │    │   → GPT-4o          │
│   (분석, 계획)     │    │   (실시간 대화)     │
└─────────────────────┘    └─────────────────────┘
    ↓                          ↓
[통합 출력 처리]              [음성 즉시 응답]
```

### 1.2 기술 스택

| 컴포넌트 | 기술 | 모델 |
|---------|------|------|
| 텍스트 처리 | OpenAI API | GPT-5 |
| 이미지 분석 | OpenAI API | GPT-5 Vision |
| 실시간 음성 | Realtime API | GPT-4o |
| 라우팅 엔진 | 자체 개발 | 규칙 기반 |

---

## 🔀 2. 라우팅 규칙 (명문화)

### 2.1 입력 유형 기반 라우팅

```python
def route_input(input_type, content, context):
    """입력 유형에 따른 모델 라우팅"""
    
    # 음성 입력 → GPT-4o (Realtime API)
    if input_type == "audio":
        return process_with_gpt4o_voice(content, context)
    
    # 텍스트/이미지 → GPT-5
    elif input_type in ["text", "image", "multimodal"]:
        return process_with_gpt5(content, context)
    
    # 응급 상황 감지
    elif detect_emergency(content):
        analysis = process_with_gpt5(content, emergency=True)
        voice_alert = process_with_gpt4o_voice(
            summarize_for_voice(analysis), 
            urgent=True
        )
        return {"analysis": analysis, "voice": voice_alert}
```

### 2.2 키워드 우선순위 처리

**응급 어휘** (최고 우선순위):
- 한국어: "아파", "분실", "사고", "도움", "응급실", "병원"
- 영어: "emergency", "help", "lost", "accident", "hospital"
- 일본어: "助けて", "病院", "事故", "紛失"

**처리 흐름**:
1. GPT-5로 상황 분석 및 정확한 정보 확인
2. GPT-4o로 간결한 구두 안내 (≤2문장)
3. 현지 연락처, 주소 제공

### 2.3 폴백 시스템

```yaml
primary_failure_handling:
  gpt4o_voice_failure:
    fallback: "GPT-5 + TTS"
    max_delay: "3초"
    user_notification: "음성 모드가 일시 중단됨"
  
  gpt5_failure:
    fallback: "GPT-4o 요약 응답"
    functionality: "제한된 정보 제공"
    escalation: "시스템 복구 알림"

connection_handling:
  low_bandwidth:
    voice_quality: "압축 모드"
    fallback: "텍스트 우선"
  
  offline_mode:
    cached_responses: "기본 여행 정보"
    sync_on_reconnect: true
```

---

## ⚙️ 3. 파라미터 맵

### 3.1 Voice 모드 (GPT-4o)

```json
{
  "model": "gpt-4o-realtime-preview",
  "voice_config": {
    "reasoning_effort": "minimal",
    "verbosity": "low",
    "max_response_length": "2문장",
    "target_latency": "600ms",
    "language_detection": "auto",
    "interruption_sensitivity": "high"
  },
  "audio_format": "pcm16",
  "sample_rate": 24000
}
```

### 3.2 정보 처리 모드 (GPT-5)

```json
{
  "model": "gpt-5",
  "reasoning_config": {
    "reasoning_effort": "medium",
    "verbosity": "medium", 
    "context_limit": "196k_tokens",
    "multimodal": true,
    "citations": "required"
  },
  "output_format": {
    "structured_data": true,
    "source_links": true,
    "confidence_scores": true
  }
}
```

### 3.3 응급 모드 (GPT-5 → GPT-4o)

```json
{
  "emergency_gpt5": {
    "reasoning_effort": "high",
    "priority": "safety_first",
    "verification": "double_check",
    "output": "structured_emergency_response"
  },
  "emergency_gpt4o": {
    "template_mode": true,
    "languages": ["ko", "en", "ja"],
    "contact_info": "prioritized",
    "calm_tone": true
  }
}
```

---

## 🌐 4. 멀티모달 규칙

### 4.1 이미지 처리 워크플로

```
사용자 이미지 업로드
    ↓
GPT-5 Vision 분석
    ↓
┌─────────────────┐
│ 메뉴/간판 감지   │ → 원문/독음/의미/알레르겐 표 생성
│ 지도/방향표     │ → 경로 분석 + 교통수단 추천
│ 영수증/티켓     │ → 가격 변환 + 예약 정보 추출
│ 응급 상황       │ → 즉시 GPT-4o 음성 알림
└─────────────────┘
    ↓
[음성 낭독 옵션]
GPT-4o: "핵심 정보만 1-2문장으로"
```

### 4.2 지도/동선 처리

**GPT-5 출력 포맷**:
```json
{
  "route_summary": {
    "origin": "현재 위치",
    "destination": "목적지",
    "total_time": "예상 시간",
    "transport": "추천 교통수단"
  },
  "step_by_step": [
    {"step": 1, "action": "지하철 3호선 탑승", "duration": "5분"},
    {"step": 2, "action": "신사역에서 하차", "duration": "15분"}
  ],
  "alternatives": ["버스 노선", "택시 예상비용"],
  "voice_summary": "지하철로 15분, 신사역 하차 후 도보 2분"
}
```

**GPT-4o 음성 출력**:
- "지하철 3호선으로 신사역까지 15분이에요"
- "하차 후 2번 출구로 나가서 직진하시면 됩니다"

---

## 🔒 5. 보안·프라이버시

### 5.1 데이터 보관 정책

```yaml
sensitive_data_handling:
  accommodation_info:
    storage: "session_only"
    ttl: "24시간"
    encryption: "AES-256"
  
  medical_info:
    storage: "no_storage"
    processing: "real_time_only"
    logging: "anonymized_only"
  
  payment_info:
    policy: "never_store"
    transmission: "encrypted_only"

voice_data_policy:
  recording: "disabled_by_default"
  transcription_logs:
    retention: "7일"
    anonymization: "automatic"
    opt_out: "available"
```

### 5.2 민감정보 감지 및 처리

```python
def handle_sensitive_info(user_input, input_type):
    """민감정보 감지 및 보호 처리"""
    
    sensitive_patterns = {
        "passport": r"\b[A-Z]{2}\d{7,9}\b",
        "credit_card": r"\b\d{4}[-\s]?\d{4}[-\s]?\d{4}[-\s]?\d{4}\b",
        "medical": ["혈압", "당뇨", "알레르기", "복용약"]
    }
    
    if detect_sensitive_data(user_input, sensitive_patterns):
        if input_type == "voice":
            return "죄송하지만 중요한 정보는 텍스트로 다시 입력해주세요"
        else:
            return process_with_encryption(user_input)
```

---

## 📊 6. 품질지표·운영

### 6.1 핵심 메트릭

| 메트릭 | 목표 | 측정 방법 |
|--------|------|-----------|
| Voice Latency | <600ms | Realtime API 응답시간 |
| 번역 정확도 | >95% | 샘플 20문 월별 평가 |
| 사실성 일치율 | >90% | 출처 링크 검증 |
| 사용자 완료도 | >80% | 태스크 완수율 |
| 시스템 가용성 | >99.5% | 업타임 모니터링 |

### 6.2 모니터링 대시보드

```yaml
realtime_monitoring:
  voice_quality:
    - latency_p95
    - interruption_success_rate
    - audio_quality_score
  
  routing_efficiency:
    - correct_model_selection_rate
    - emergency_detection_accuracy
    - fallback_trigger_frequency
  
  user_satisfaction:
    - conversation_completion_rate
    - user_retry_frequency
    - support_escalation_rate
```

### 6.3 알림 시스템

```yaml
alerts:
  critical:
    - voice_latency > 2초
    - emergency_detection_failure
    - system_unavailable > 30초
  
  warning:
    - accuracy_drop > 5%
    - unusual_traffic_pattern
    - api_rate_limit_approaching
```

---

## 🧪 7. 테스트 시나리오 (샘플)

### 7.1 통역 테스트

**시나리오 1**: 메뉴 번역 + 알레르기 체크
```
입력: [메뉴 사진 + "새우 알레르기 있어요"]
GPT-5: 메뉴 분석, 새우 포함 항목 식별, 안전 옵션 추천
GPT-4o: "3번과 7번 메뉴에 새우가 들어있어요. 2번 치킨이 안전합니다"
```

**시나리오 2**: 복합 질의 처리
```
입력: "주유소 어디?" (음성)
GPT-4o: "200m 앞 오른쪽에 GS칼텍스가 있습니다"
GPT-5: [지도 링크, 가격 정보, 영업시간 표] 동시 제공
```

### 7.2 응급 상황 테스트

**시나리오 3**: 의료 응급상황
```
입력: "갑자기 가슴이 아파요" (음성)
GPT-5: 증상 분석, 근처 병원 검색, 교통편 확인
GPT-4o: "가까운 응급실은 신촌세브란스입니다. 택시로 7분 거리예요"
+ 119 연락방법, 병원 주소, 간단한 응급처치 가이드
```

### 7.3 성능 벤치마크

```python
test_scenarios = {
    "translation_accuracy": {
        "sample_size": 20,
        "languages": ["ko-en", "ko-ja", "en-ja"],
        "frequency": "weekly",
        "pass_threshold": 0.95
    },
    "travel_qa": {
        "sample_size": 10,
        "categories": ["교통", "숙박", "음식", "관광"],
        "frequency": "monthly", 
        "pass_threshold": 0.90
    },
    "emergency_response": {
        "sample_size": 5,
        "scenarios": ["의료", "분실", "사고", "치안"],
        "frequency": "monthly",
        "pass_threshold": 1.0
    }
}
```

---

## 🔄 8. 변경 로그 및 향후 대비

### 8.1 2025년 9월 9일 이후 변경사항

| 항목 | 변경 전 | 변경 후 | 영향도 |
|------|---------|---------|--------|
| Voice 모드명 | Standard/Advanced | ChatGPT Voice | 낮음 |
| 음성 엔진 | GPT-3.5/GPT-4o 혼재 | GPT-4o 통합 | 중간 |
| API 호출 | 복수 엔드포인트 | Realtime API 통합 | 높음 |
| 지연시간 | 2.8-5.4초 | <600ms | 높음 |

### 8.2 향후 GPT-5 Voice 전환 대비

**예상 변경 포인트** (OpenAI 발표 시):

```yaml
preparation_checklist:
  api_migration:
    - realtime_api_endpoint_update
    - parameter_mapping_adjustment  
    - latency_optimization_review
  
  performance_validation:
    - voice_quality_comparison
    - accuracy_benchmark_rerun
    - user_acceptance_testing
  
  rollback_plan:
    - gpt4o_fallback_maintenance
    - gradual_migration_strategy
    - monitoring_enhancement
```

### 8.3 기술 부채 관리

**현재 제약사항**:
1. GPT-5 음성 기능 부재로 인한 이중 시스템
2. 모델 간 컨텍스트 전달 복잡성
3. 일관된 personality 유지 어려움

**개선 계획**:
1. 컨텍스트 브릿지 최적화
2. 통합 personality 템플릿 개발
3. 모니터링 자동화 확대

---

## 📝 9. 구현 체크리스트

### 9.1 Phase 1: 기반 구축 (2주)
- [ ] GPT-5 API 연동 및 테스트
- [ ] GPT-4o Realtime API 연동
- [ ] 기본 라우팅 로직 구현
- [ ] 입력 유형 감지 모듈 개발

### 9.2 Phase 2: 여행 기능 구현 (3주)  
- [ ] 메뉴/간판 이미지 분석
- [ ] 실시간 번역 기능
- [ ] 지도/경로 안내 시스템
- [ ] 응급상황 대응 로직

### 9.3 Phase 3: 최적화 및 테스트 (2주)
- [ ] 성능 벤치마크 실행
- [ ] 사용자 테스트 및 피드백 수집
- [ ] 보안 감사 및 개선
- [ ] 문서화 완료

---

## 🎯 10. 성공 기준

### 10.1 기술적 성공 기준
- Voice 응답 지연 <600ms 달성률 >95%
- 번역 정확도 >95% (샘플 테스트)
- 시스템 가용성 >99.5%
- 응급상황 감지 정확도 100%

### 10.2 사용자 경험 성공 기준  
- 대화 완료율 >80%
- 사용자 재시도율 <10%
- 만족도 점수 >4.5/5.0
- 지원팀 에스컬레이션 <5%

---

**문서 버전**: v1.0  
**작성일**: 2025년 9월 5일  
**업데이트 주기**: 월 1회 또는 주요 변경사항 발생 시  
**승인**: [프로젝트 매니저명]  
**검토**: [기술 리드명]