// pch.h or Common.h <- 헤더들을 모아서 한번에 선언하는 헤더
#pragma once

//입출력 및 문자열 헤더
#include <iostream>			// 콘솔 입출력
#include <string>			// 문자열 데이터
#include <fstream>			// 파일 입출력(세이브, 로드)
#include <sstream>			// 문자열 분리 또는 데이터를 문자열로 합치기
#include <format>			// (C++20) 변수를 깔끔한 형식의 문자열로 조립
//#include <print>			// (C++23) iostream보다 더 빠르게 콘솔 텍스트 출력 (사용 x)
// 자료구조 헤더
#include <vector>			// 데이터 개수에 따라 크기 조절되는 동적 배열
#include <unordered_map>	// 이름표(key)를 달아 데이터(value)를 저장하고 빠르게 검색하는 테이블
#include <deque>			// 앞과 뒤 양쪽에서 데이터를 추가하거나 삭제할 수 있는 양방향 대기열
#include <set>				// 중복을 허용하지 않고 데이터를 항상 정렬시켜 저장하는 집합
// 핵심 유틸리티 및 알고리즘 헤더
#include <algorithm>		// 데이터를 정렬(sort), 검색(find)하는 등 편리한 표준 알고리즘 모음
#include <random>			// 전투 데미지 계산, 아이템 드롭 등 게임 내 난수 생성
#include <functional>		// 함수를 변수처럼 다루거나, 특정 행동을기억해두고 나중에 실행(콜백)함
#include <optional>			// 값이 존재할 수도, 없을 수도 있는 상태를 안전하게 표시
#include <cassert>			// assert()를 사용해 개발 중 논리적인 오류나 버그를 빠르게 찾음
// 시간 및 시스템 제어 헤더
#include <chrono>			// 프레임 사이의 시간을 계산하거나 정밀한 시간을 측점함
#include <thread>			// CPU 과부화 방지를 위한 대기 시간 등 스레드를 제어
#include <conio.h>			// (윈도우 전용) 엔터 키를 누르지 않아도 키보드 입력(_getch())를 즉각적으로 받음

#ifdef _WIN32
#include <windows.h>		// (윈도우 전용) 콘솔의 커거 위치를 이동하는 등의 OS종속적인 기능을 다룸
#endif // _WIN32

