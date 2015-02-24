#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include "function.h"
#include "keybios.h"

// Note: test cases should all be lower case!!!

typedef bool (*test_func)();

const double eps = 0.001;
char key_names[256][16];

void str2num( unsigned char * );

void init_key_names() {
    memset(key_names, 0, sizeof(key_names));
    strcpy(key_names[KEY_CHAR_PLUS], "KEY_CHAR_PLUS");
    strcpy(key_names[KEY_CHAR_MINUS], "KEY_CHAR_MINUS");
    strcpy(key_names[KEY_CHAR_MULT], "KEY_CHAR_MULT");
    strcpy(key_names[KEY_CHAR_DIV], "KEY_CHAR_DIV");
    strcpy(key_names[KEY_CHAR_POW], "KEY_CHAR_POW");
    strcpy(key_names[KEY_CHAR_LPAR], "KEY_CHAR_LPAR");
    strcpy(key_names[KEY_CHAR_RPAR], "KEY_CHAR_RPAR");
    strcpy(key_names[KEY_CHAR_SIN], "KEY_CHAR_SIN");
    strcpy(key_names[KEY_CHAR_COS], "KEY_CHAR_COS");
    strcpy(key_names[KEY_CHAR_TAN], "KEY_CHAR_TAN");
    strcpy(key_names[KEY_CHAR_LOG], "KEY_CHAR_LOG");
    strcpy(key_names[KEY_CHAR_LN], "KEY_CHAR_LN");
    strcpy(key_names[KEY_CHAR_EXP], "KEY_CHAR_EXP");
    strcpy(key_names[KEY_CHAR_ROOT], "KEY_CHAR_ROOT");
    strcpy(key_names[KEY_CHAR_PMINUS], "KEY_CHAR_PMINUS");
    strcpy(key_names[KEY_CHAR_DP], "KEY_CHAR_DP");
    strcpy(key_names[KEY_CHAR_0], "KEY_CHAR_0");
    strcpy(key_names[KEY_CHAR_1], "KEY_CHAR_1");
    strcpy(key_names[KEY_CHAR_2], "KEY_CHAR_2");
    strcpy(key_names[KEY_CHAR_3], "KEY_CHAR_3");
    strcpy(key_names[KEY_CHAR_4], "KEY_CHAR_4");
    strcpy(key_names[KEY_CHAR_5], "KEY_CHAR_5");
    strcpy(key_names[KEY_CHAR_6], "KEY_CHAR_6");
    strcpy(key_names[KEY_CHAR_7], "KEY_CHAR_7");
    strcpy(key_names[KEY_CHAR_8], "KEY_CHAR_8");
    strcpy(key_names[KEY_CHAR_9], "KEY_CHAR_9");
    strcpy(key_names[KEY_CHAR_COMMA], "KEY_CHAR_COMMA");
    strcpy(key_names[KEY_CHAR_X], "KEY_CHAR_X");
}

void output_names( unsigned char * func ) {
    for ( unsigned i = 0; i < strlen((char *)func); i++ ) {
        puts(key_names[func[i]]);
    }
}

unsigned char str2btn( char *str ) {
    if ( strcmp(str, "+") == 0 ) return KEY_CHAR_PLUS;
    if ( strcmp(str, "-") == 0 ) return KEY_CHAR_MINUS;
    if ( strcmp(str, "(-)") == 0 ) return KEY_CHAR_PMINUS;
    if ( strcmp(str, "*") == 0 ) return KEY_CHAR_MULT;
    if ( strcmp(str, "/") == 0 ) return KEY_CHAR_DIV;
    if ( strcmp(str, "^") == 0 ) return KEY_CHAR_POW;

    if ( strcmp(str, "x") == 0 ) return KEY_CHAR_X;

    if ( strcmp(str, "(") == 0 ) return KEY_CHAR_LPAR;
    if ( strcmp(str, ")") == 0 ) return KEY_CHAR_RPAR;

    if ( strcmp(str, "sin(") == 0 ) return KEY_CHAR_SIN;
    if ( strcmp(str, "cos(") == 0 ) return KEY_CHAR_COS;
    if ( strcmp(str, "tan(") == 0 ) return KEY_CHAR_TAN;
    if ( strcmp(str, "log(") == 0 ) return KEY_CHAR_LOG;
    if ( strcmp(str, "ln(") == 0 ) return KEY_CHAR_LN;
    if ( strcmp(str, "exp(") == 0 ) return KEY_CHAR_EXP;
    if ( strcmp(str, "sqrt(") == 0 ) return KEY_CHAR_ROOT;

    return 0;
}

bool test_case_01() {
    char filenames[][16] = {
        "test/test01",
    };
    unsigned char sym_buf[32], line_buf[512];
    unsigned char func[FUNC_LEN], ch, tmp[2];
    double correct, result;
    Function f;
    int sub_case_idx = 1;
    bool test_result = true;
    for ( auto item: filenames ) {
        //打开测试文件
        std::string name(item);
        FILE *in_fid = fopen((name + ".in").c_str(), "r");
        FILE *out_fid = fopen((name + ".out").c_str(), "r");
        //读入一输入行数据
        while ( fgets((char *)line_buf, 512, in_fid) != NULL ) {
            if ( line_buf[0] == 0 ) continue;
            //读入一个正确结果
            fscanf(out_fid, "%lf", &correct);
            //然后从输入数据构造按键序列
            memset(func, 0, sizeof(func));
            std::istringstream iss((char *)line_buf);
            while ( iss >> sym_buf ) {
                if ( (ch = str2btn((char *)sym_buf)) != 0 ) {
                    tmp[0] = ch; tmp[1] = 0;
                    strcat((char *)func, (char *)tmp);
                } else {
                    str2num(sym_buf);
                    strcat((char *)func, (char *)sym_buf);
                }
            }
            //设置函数体并求值
            f.set_func(func);
            //检查结果
            result = f(1.2798);
            if ( f.error() ) {
                puts("Syntax error! Check your test case!");
                exit(-1);
            } else {
                if ( fabs(correct - result) < eps ) {
                    printf("\tSub test case %02d passed.\n", sub_case_idx++);
                } else {
                    printf("\tSub test case %02d failed:\n", sub_case_idx++);
                    printf("\t\tCorrect answer is %f while your result is %f\n", correct, result);
                    test_result = false;
                }
            }
        }
        fclose(in_fid);
        fclose(out_fid);
    }
    return test_result;
}

bool test_case_02() {
    char filenames[][16] = {
        "test/test02",
    };
    unsigned char sym_buf[32], line_buf[512];
    unsigned char func[FUNC_LEN], ch, tmp[2];
    Function f;
    int sub_case_idx = 1;
    bool test_result = true;
    for ( auto item: filenames ) {
        //打开测试文件
        std::string name(item);
        FILE *in_fid = fopen((name + ".in").c_str(), "r");
        //读入一输入行数据
        while ( fgets((char *)line_buf, 512, in_fid) != NULL ) {
            if ( line_buf[0] == 0 ) continue;
            //然后从输入数据构造按键序列
            memset(func, 0, sizeof(func));
            std::istringstream iss((char *)line_buf);
            while ( iss >> sym_buf ) {
                if ( (ch = str2btn((char *)sym_buf)) != 0 ) {
                    tmp[0] = ch; tmp[1] = 0;
                    strcat((char *)func, (char *)tmp);
                } else {
                    str2num(sym_buf);
                    strcat((char *)func, (char *)sym_buf);
                }
            }
            //设置函数体并求值
            f.set_func(func);
            //调用求值
            f(0.);
            if ( f.error() ) {
                printf("\tSub test case %02d passed.\n", sub_case_idx++);
            } else {
                printf("\tSub test case %02d failed:\n", sub_case_idx++);
                printf("\t\tYou should return syntax error!\n");
                test_result = false;
            }
        }
        fclose(in_fid);
    }
    return test_result;
}


int main()
{
    init_key_names();
    std::vector<test_func> func;
    func.push_back(test_case_01);
    func.push_back(test_case_02);
    for ( unsigned i = 0; i < func.size(); i++ ) {
        printf("Running test case No.%02u ...\n", i + 1);
        if ( func[i]() ) {
            printf("Test case No.%02u passed !\n", i + 1);
        } else {
            printf("Test case No.%02u failed !\n", i + 1);
        }
        puts("");
    }
}
