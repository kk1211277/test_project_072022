??????? ??????? ????????? ??????? ? ?????????????? ??????.

??????? ??? ???????:
	ShapeAPI - ??????????? API ? ???? ?????????? DLL;
	test_3d - ????????? ???????????? ShapeAPI.dll.

??????? ??????? ? ?????? MSVC 19 ? Qt 5.12 (MinGW 64-dit). C++14.

??? ??????????? ????? ?? ?????? ??????????? ??????? "get_point(double t)".
??? ??????????? ??????? ?????? ??????????? ??????????? ??????? "get_vector_dr(double t)" ? "get_vector_T(double t)".
	get_vector_dr(double t) - ???????????? ?????? ???????????
	get_vector_T(double t) - ???????????? ????????? ?????? ???????????
?????? ????? ????? ?????? ???????????? ??? ???????????, ????????? ????? ????? {0, 0, 0} (? ??? ????? ??????, ??????? ?? ?????? ?????????? ? ??????????? ?????? ?? ???????? ????? ?? ??????).

??? ?????? ?????? ??????????? ??????? "print(double t, int param)".
	??? param = 0 - ??????????? get_vector_dr(double t)
	??? param = 1 - ??????????? get_vector_T(double t)

?????? ????? ???????? ???????????? ? ????????????? ?????? ?????????????? ???????????? ?????????? C++14.
