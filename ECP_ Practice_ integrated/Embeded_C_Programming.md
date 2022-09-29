# 임베디드 C 프로그래밍 실습자료

## 목록

<br/>

>> <strong> 구분 : 메모리 모델 </strong>

<br/>

<p align="center">

| 이름 | 내용 |
|:---|:---:|
|  정수 표현 | 부호있는 정수와 부호없는 정수의 표현 방법 |
|  Byte Ordering | Little endian & big endian |
|  구조체  | 구조체 표현 방법, 구조체의 크기, 패딩, 바이트 정렬, 비트 단위 사용 |
|  공용체 | 공용체 사용 방법, 구조체와 공용체의 결합 |
|  포인터  | 포인터의 원리, * 및 & 키워드 활용 |
|  배열  | 포인터와 배열의 관계, 2차원 및 3차원 배열 활용과 포인터 활용, 주소 계산 |
|  volatile  | volatile 키워드 활용 |
|  메모리 접근  | 주소를 이용해 직접 메모리에 접근하는 방법 |
|  함수 포인터  | 함수 포인터의 활용 |

</p>

<br/>

>> <strong> 구분 : 변수 활용 </strong>

<br/>

<center>

| 이름 | 내용 |
|:---|:---:|
|  변수 별 사용  | 전역변수, 지역변수, 정적 (전역 & 지역)변수의 활용 |
|  비트 조작  | 원하는 비트 설정, 클리어, 토글 방법 |
|  전역변수의 위험성  | 전역변수를 ISR에서 사용할 경우 위험성 |
|  함수 매개변수 전달  | Call-by-value & call-by-reference, const 키워드 |
|  고정 소수점   | 부동 소수점을 고정 소수점으로 변환하여 사용 |


</center>

<br/>

>> <strong> 구분 : RTOS </strong>

<br/>

<center>

| 이름 | 내용 |
|:---|:---:|
|  태스크 스케줄링   | RMS (Rate-monotonic scheduling) 설명 |
|  스케줄 가능 분석   | 여러 태스크의 실행 시간 기준으로 스케줄 가능 분석 |
|  동기화   | 여러 태스크 사이의 공유 데이터 동기화 |

</center>

<br/>

>> <strong> 구분 : 최적화 </strong>

<br/>

<center>

| 이름 | 내용 |
|:---|:---:|
|  변수 사용    | 각 변수 종류별 실행 시간 측정 및 비교 |
|  배열과 포인터    | 배열과 포인터를 사용하는 코드 실행 시간 측정 및 비교 |
|  매개변수 갯수    | 매개변수 갯수에 대한 실행 시간 측정 및 비교 |

</center>

<br/>

>> <strong> 구분 : 테스팅  </strong>

<center>

| 이름 | 내용 |
|:---|:---:|
|     |  |
|  MC/DC 분석    |  |
|     |  |

</center>

***


## 정수 표현

> <strong>  예제1 : 부호 있는 정수와 부호 없는 정수   </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/정수표현_1_1.jpg">
</p>

***

## Byte Ordering

>  <strong> 예제1 : Byte ordering (Little endian)  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/Byte Ordering_1_1.jpg">
</p>

***

## 구조체

>  <strong> 예제1 : 구조체 표현 방법  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_1_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_1_2.jpg">
</p>

>  <strong> 예제2 : 구조체의 크기, 패딩, 바이트 정렬  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_2_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_2_2.jpg">
</p>

>  <strong> 예제3: 구조체의 비트단위 사용  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_3_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/구조체_3_2.jpg">
</p>

***

## 공용체

>  <strong> 예제1 : 공용체 사용 방법  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_1_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_1_2.jpg">
</p>

>  <strong> 예제2 : 구조체와 공용체의 결합  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_2_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_2_2.jpg">
</p>

***

## 포인터

>  <strong> 예제1 : 변수 타입과 포인터 변수 타입의 크기 비교 </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_1_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_1_2.jpg">
</p>

>  <strong> 예제2 : 포인터 변수와 *, & 키워드 및 포인터와 메모리 주소 관계 학습  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_2_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/공용체_2_2.jpg">
</p>

***

## 배열

>  <strong> 예제1 : 포인터와 배열의 관계 </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_1_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_1_2.jpg">
</p>

>  <strong> 예제2 : 2차원 배열에서의 포인터 연산 학습과 포인터 연산과 반복문을 이용한 전체 배열 정보 출력  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_2_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_2_2.jpg">
</p>

>  <strong> 예제3 : 3차원 배열에서의 포인터 연산 학습과 포인터 연산과 반복문을 이용한 전체 배열 정보 출력  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_3_1.jpg">
</p>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/배열_3_2.jpg">
</p>


***

## Volatile

>  <strong>  예제1 : Volatile 키워드 사용 </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/Volatile_1_1.jpg">
</p>

***

## 메모리 접근

>  <strong>  예제1 : 주소를 이용해 직접 메모리에 접근 </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/메모리접근_1_1.jpg">
</p>

***

## 함수 포인터

>  <strong>  예제1 : 함수 포인터를 활용한 함수 호출 </strong>


<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/함수포인터_1_1.jpg">
</p>


>  <strong>  예제2 : 함수 포인터 배열을 활용한 함수 호출 </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/함수포인터_2_1.jpg">
</p>


***

## 변수 별 사용

>  <strong>  예제1 : 전역,지역, 정적 변수의 활용  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/변수별사용_1_1.jpg">
</p>

***

## 비트 조작

>  <strong>  예제1 : 원하는 비트 설정, 클리어, 토글 수행  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/비트조작_1_1.jpg">
</p>

***

## 함수 매개변수 전달

>  <strong>  예제1 : Call-by-value & Call-by-reference  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/함수매개변수전달_1_1.jpg">
</p>

>  <strong>  예제2 : const 키워드  </strong>

<p align="center">
 <img src = "./ECP_ Practice_ integrated_Picture/함수매개변수전달_2_1.jpg">
</p>


***
