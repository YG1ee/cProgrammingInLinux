/* 
 * strtok은 string token을 의미하는데, 여기서 token은
 * 문장을 여러 부분으로 나눌 때 쓰는 구분자를 의미함.
 */

#include <stdio.h>
#include <string.h> /* strtok 함수가 정의된 헤더 파일 */

main() { // main의 타입 (int, void) 을 지정하지 않아도 컴파일, 실행 가능
    char str[] = "Hello Linux C Programming";
    
    /*
     * 어떤 구분자를 기준으로 단어로 자를지를 지정하는데
     * 이 프로그램에서는 공백 문자(" ")를 이용하고 만약
     * 구분자로 ;, :을 이용하려면 ";:"을 지정하면 됨
     */

    char delim[]= " ";
    char *ptr;

    /*
     * 문자열 str에서 delim 구분자가 나오면 단어로 자르고
     * 단어의 첫 글자에 대한 포인터 반환
     */

    ptr = strtok(str, delim);
    printf("%s\n", ptr);
    /* 두 번째 호출부터는 NULL로 설정해야 함 */
    while(ptr = strtok(NULL, delim))
        printf("%s\n", ptr);
}

