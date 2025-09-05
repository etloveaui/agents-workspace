# 📂 \[MN\&FK] Travel AI — 프로젝트 파일 체크리스트

## ✅ 등록 완료 파일

* [ ] `miyakojima_guide.md`
  ⬩ 지역별 특징·맛집·관광 정보
* [ ] `japanese_phrases.md`
  ⬩ 상황별 일본어 표현, 발음·번역 포함
* [ ] `emergency_info.md`
  ⬩ 응급 표현, 연락처, 병원/경찰/영사관 정보
* [ ] `personal_travel_info.md`
  ⬩ 숙소·차량·항공편·개인 취향 (지속 업데이트 필요)

---

## 📌 추가 예정 (스키마 기반 생성 필요)

* [ ] `poi.csv`
  ⬩ 명소/맛집/카페 등 장소 데이터
  ⬩ 필드: `poi_id, name, lat, lon, tags, open_hours, cost, stay_min, rating, notes`

* [ ] `route.geojson`
  ⬩ A→B 이동 경로 데이터 (일자별 동선)
  ⬩ GeoJSON LineString 구조

* [ ] `itinerary.csv`
  ⬩ 일정표 (일자/시간대/활동/장소)
  ⬩ 필드: `day, slot, start, end, area, activity, poi_ids, notes`

* [ ] `constraints.json`
  ⬩ 개인 제약 조건 (예산, 알레르기, 피하고 싶은 요소)
  ⬩ 예시: `{"diet":["no_pork"],"allergy":["shellfish"],"budget_meal":"~2000JPY","avoid":["long_queue"]}`

---

## 🔄 유지·업데이트 규칙

* **`personal_travel_info.md`**: 여행 준비가 진척될수록 숙소/차량/일정 업데이트
* **`poi.csv`**: 직접 찾은 맛집·명소 추가 시 갱신
* **`itinerary.csv`**: 최종 일정 확정 후 업로드
* **`constraints.json`**: 예산, 취향, 알레르기 정보가 바뀌면 수정

---

👉 이 체크리스트대로만 파일을 관리하면 프로젝트가 깔끔하게 유지됩니다.

원하시나요? 제가 이걸 \*\*빈 템플릿 세트 (csv/json/md 샘플)\*\*로도 만들어드릴까요, 직접 쓰기 편하게?
