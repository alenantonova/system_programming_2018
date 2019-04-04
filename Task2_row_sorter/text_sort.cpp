#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>
#include<algorithm>

//компаратор для сравнения строк по указателям на их начала
int comparator(const char* p1, const char* p2) {
    std::string str1, str2;
    for(char* pi = (char *)p1; *pi !=  '\0'; pi++) {
        if (isalpha(*pi)) {
            str1.push_back(*pi);
        }
    }
    for(char* pi = (char *)p2; *pi !=  '\0'; pi++) {
        if (isalpha(*pi)) {
            str2.push_back(*pi);
        }
    }
    return str1 < str2;
}

//обратное сравнение строк по указателям на их начала
int reverse_comparator(const char* p1, const char* p2) {
    std::string str1, str2;
    for(char* pi = (char *)p1; *pi !=  '\0'; pi++) {
        if (isalpha(*pi)) {
            str1.push_back(*pi);
        }
    }
    for(char* pi = (char *)p2; *pi !=  '\0'; pi++) {
        if (isalpha(*pi)) {
            str2.push_back(*pi);
        }
    }
    std::reverse(str1.begin(), str1.end());
    std::reverse(str2.begin(), str2.end());
    return str1 < str2;
}

long get_file_len (FILE * f) {
    fseek(f,0,SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    if(!len) {
        printf("Входной файл пустой\n");
        return -1;
    }
    return len;
}

void fill_pointer_arr(char *text, size_t len, std::vector<char *> &starts, size_t &num_of_str) {
    starts.push_back(&text[0]);
    //заменяем символы переноса строк на 0-символы
    for(int i = 1; i < len; i++) {
        if(text[i] == '\n') {
            text[i] = '\0';
            starts.push_back(&text[i+1]);
            num_of_str++;
        }
    }
}

void write_result(FILE * f_out, std::string msg, size_t arr_size, std::vector<char *> starts) {
    fprintf(f_out, "%s\n", msg.c_str());
    for(int i = 0; i < arr_size; ++i) {
        fprintf(f_out, "%s\n", starts[i]);
    }
}

void sort_file(std::string file_in, std::string file_out) {
    FILE * f_out = fopen(file_out.c_str(), "w");
    FILE * f = fopen(file_in.c_str(), "r");
    if(! f || !f_out) {
        printf("не удается открыть файл\n");
        return;
    }

    long len = get_file_len(f);
    char * text = new char[len+1]; //входные данные
    fread(text, sizeof(char), len, f);
    fclose(f);

    text[len] = '\0';
    size_t num_of_strings = 0;
    std::vector<char *> str_start; //массив указателей на начала строк
    fill_pointer_arr(text, len, str_start, num_of_strings);
    std::vector<char *> str_start_sorted(str_start);

    std::sort(str_start_sorted.begin(), str_start_sorted.end(), comparator);
    write_result(f_out, "Результат сортировки строк, сравнением слева направо:",
                 num_of_strings, str_start_sorted);

    std::sort(str_start_sorted.begin(), str_start_sorted.end(), reverse_comparator);
    write_result(f_out, "\nРезультат сортировки строк, сравнением справа налево:",
                 num_of_strings, str_start_sorted);

    write_result(f_out, "\nОригинальный текст", num_of_strings, str_start);

    fclose(f_out);
    delete [] text;

}

int main() {
    try {
        std::string filename_in, filename_out;
        printf("Введите имя файла с текстом\n");
        std::cin >> filename_in;
        printf("Введите имя файла для записи результата\n");
        std::cin >> filename_out;

        sort_file(filename_in, filename_out);
    } catch (std::bad_alloc) {
        printf("Error while allocating memory.\n");
    }

    return 0;
}