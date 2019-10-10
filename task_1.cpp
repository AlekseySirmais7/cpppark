/*
  Создать структуру для хранения информации о заинтересованных сторонах проекта:
их роли (заказчик, покупатель, разработчик и пр.), наименовании или имени, степени влияния и т.д.
Составить с ее использованием программу вывода информации обо всех заинтересованных лицах,
наиболее соответствующих заданным пользователем критериям.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_INPIT_BUFFER_SIZE 200
#define MAX_INPIT_BUFFER_SIZE_STRING "200"
#define INPUT_STRING_FORMAT "%" MAX_INPIT_BUFFER_SIZE_STRING "s"
#define INPUT_NUMBER_FORMAT "%lu"
const size_t MAX_NAME_SIZE = MAX_INPIT_BUFFER_SIZE;
const size_t MAX_ROLE_SIZE = MAX_INPIT_BUFFER_SIZE;
const size_t MAX_MEMBER_SIZE = 6;  // 6 - max, use:[0..6]
const size_t MAX_INPUT_BUFFER = MAX_INPIT_BUFFER_SIZE;
const size_t STRUCT_FIELD_COUNT = 7;
const size_t MIN_SHOW_MATCHES = 2; // минимальное количество соответсвий для показа

typedef struct project_member{
    char * role;
    char * name;
    bool work_with_project;
    bool use_project;
    unsigned char influence:4;  // [0..15]
    bool finances_project;
    bool danger;
} project_member;

typedef struct answer {
    size_t size;
    project_member ** arr_ptr;
    size_t * arr_matches_count;
} answer;

void check_print(const char * string);
void create_members(project_member *const members, const size_t members_size);
void free_members(project_member *const members, const size_t members_size);
project_member * create_requirements(const size_t struct_field_count);
void free_requirements(const project_member *const requirements);
bool set_parameters(project_member *const requirements, const size_t struct_field_count);
bool check_strig_input(char *const buffer);
bool check_bool_input(char *const buffer);
bool is_true(char *const buffer);
bool check_number_input(size_t *const influence_number);
bool show_requirements(project_member *const requirements);
answer * create_answer(size_t max_member_size);
void free_answer(answer * ans);
bool equal_strings(char *const string1, char *const string2, size_t max_string_size);
bool find_snswer(project_member *const members, const size_t member_size,
                project_member * requirements, answer * ans);
void swap_size_t(size_t * a, size_t * b);
void swap_p_m(project_member ** a, project_member ** b);
size_t sort_for_output(answer * ans, const size_t member_iter);
void showAns(answer * ans);


int main() {
    project_member *const members = (project_member *const) calloc(MAX_MEMBER_SIZE,
                                    sizeof(project_member));
    create_members(members, MAX_MEMBER_SIZE);

    project_member *const requirements = (project_member *)malloc(sizeof(project_member));

    if (!set_parameters(requirements, STRUCT_FIELD_COUNT))
        assert(false);

    if(!show_requirements(requirements))
        assert(false);

    answer * ans = create_answer(MAX_MEMBER_SIZE);

    if (find_snswer(members, MAX_MEMBER_SIZE, requirements, ans))
        showAns(ans);
    else
        check_print("No elements for your requirements\n");

    free_answer(ans);
    free_requirements(requirements);
    free(requirements);
    free_members(members, MAX_MEMBER_SIZE);
    return 0;
}

void check_print(const char * string){
    if (printf("%s", string) < 0)
        assert(false);
}

void create_members(project_member *const members, const size_t membersSize){
    assert(membersSize <= MAX_MEMBER_SIZE);
    for (size_t i = 0; i<membersSize; i++) {
        members[i].name = (char *)calloc(MAX_NAME_SIZE, sizeof(char));
        members[i].role = (char *)calloc(MAX_ROLE_SIZE, sizeof(char));
        switch (i) {
        case 0:
            {  // заказчик
            members[i].name = (char *)"alex";
            members[i].role = (char *)"employer";
            members[i].work_with_project = false;
            members[i].use_project = false;
            members[i].influence = 10;
            members[i].finances_project = true;
            members[i].danger = false;
            break;
            }
        case 1:
            { // покупатель
            members[i].name = (char *)"dima";
            members[i].role = (char *)"customer";
            members[i].work_with_project = false;
            members[i].use_project = true;
            members[i].influence = 6;
            members[i].finances_project = false;
            members[i].danger = false;
            break;
            }
        case 2:
            {  //разработчик
            members[i].name = (char *)"ann";
            members[i].role = (char *)"developer";
            members[i].work_with_project = true;
            members[i].use_project = true;
            members[i].influence = 5;
            members[i].finances_project = false;
            members[i].danger = false;
            break;
            }
        case 3:
            {  // пиарщик
            members[i].name = (char *)"vova";
            members[i].role = (char *)"advertiser";
            members[i].work_with_project = false;
            members[i].use_project = false;
            members[i].influence = 6;
            members[i].finances_project = false;
            members[i].danger = false;
            break;
            }
        case 4:
            {  //конкурент
            members[i].name = (char *)"eva";
            members[i].role = (char *)"opponent";
            members[i].work_with_project = false;
            members[i].use_project = false;
            members[i].influence = 5;
            members[i].finances_project = false;
            members[i].danger = true;
            break;
            }
        case 5:
            {  //potential customer
            members[i].name = (char *)"slava";
            members[i].role = (char *)"PC";
            members[i].work_with_project = false;
            members[i].use_project = false;
            members[i].influence = 0;
            members[i].finances_project = false;
            members[i].danger = false;
            break;
            }
        default:
            { 
            assert(false);
            break;
            }
        }
    }
}

void free_members(project_member *const members, const size_t membersSize) {
    for (size_t i = 0; i<membersSize; i++) {
        free(members[i].name);
        free(members[i].role);
    }
    free(members);
}

void free_requirements(const project_member *const requirements) {
    free(requirements->name);
    free(requirements->role);
}

bool check_strig_input(char *const buffer) {
    if (scanf(INPUT_STRING_FORMAT, buffer) != 1)
        return false;
    return true;
}

bool check_bool_input(char * buffer) {
    if (MAX_INPUT_BUFFER <= 4)  // need 3 and ('\0') for "yes"
        return false;
    if (scanf(INPUT_STRING_FORMAT, buffer) != 1)
        return false;
    if ( (buffer[0]=='y' && buffer[1]=='e'&& buffer[2]=='s' && buffer[3]=='\0')
         || (buffer[0]=='n' && buffer[1]=='o' && buffer[2]=='\0') )
        return true;
    else
        return false;
}

bool is_true(char *const buffer) {
    if (buffer[0]=='y' && buffer[1]=='e'&& buffer[2]=='s' && buffer[3]=='\0')
        return true;
    else
        return false;
}

bool check_number_input(size_t *const influenceNumber) {
    if (scanf(INPUT_NUMBER_FORMAT, influenceNumber) != 1)
        return false;
    if ( *(influenceNumber) > 15)
        return false;
    else
        return true;
}

bool set_parameters(project_member *const requirements, const size_t structFieldCount) {
    char * buffer = (char *)calloc(MAX_INPUT_BUFFER, sizeof(char));
    requirements->name = (char*)calloc(MAX_NAME_SIZE, sizeof(char)); // free in freeRequirements()
    requirements->role = (char*)calloc(MAX_ROLE_SIZE, sizeof(char));
    size_t step = 0;
    while(true){
        if (step >= structFieldCount) break;
        switch(step){
        case 0:
            {
            check_print("Name:");
            if (check_strig_input(buffer)){
                memcpy(requirements->name,buffer, MAX_INPUT_BUFFER);
                step++;
            }
            else {
                fflush(stdin);
                check_print("Bad name input, try one more time\n");
                continue;
            }
            break;
            }
        case 1:
            {
            check_print("Role:");
            if (check_strig_input(buffer)) {
                memcpy(requirements->role,buffer, MAX_INPUT_BUFFER);
                step++;
            }
            else {
                fflush(stdin);
                check_print("Bad role input, try one more time\n");
                continue;
            }
            break;
            }
        case 2:
            {
            check_print("Work with project(yes//no):");
            if (check_bool_input(buffer)) {  // check input in fun
                if (is_true(buffer)) {
                    requirements->work_with_project = true;
                    step++;
                }
                else {
                    requirements->work_with_project = false;
                    step++;
                }
            }
            else {
                fflush(stdin);
                check_print("Bad (yes//no) input, try one more time\n");
                continue;
            }
            break;
            }
        case 3:
            {
            check_print("Use project(yes//no):");
            if (check_bool_input(buffer)) {  // check input in fun
                if (is_true(buffer)) {
                    requirements->use_project = true;
                    step++;
                }
                else {
                    requirements->use_project = false;
                    step++;
                }
            }
            else {
                fflush(stdin);
                check_print("Bad (yes//no) input, try one more time\n");
                continue;
            }
            break;
            }
        case 4:
            {
            check_print("Influence[0-15]:");
            size_t *const influenceNumber = (size_t*)malloc(sizeof(size_t));
            if (check_number_input(influenceNumber)) {
                requirements->influence = *influenceNumber;
                free(influenceNumber);
                step++;
            }
            else {
                fflush(stdin);
                check_print("Bad influence input, try one more time\n");
                free(influenceNumber);
                continue;
            }
            break;
            }
        case 5:
            {
            check_print("Finance(yes//no):");
            if (check_bool_input(buffer)) {  // check input in fun
                if (is_true(buffer)) {
                    requirements->finances_project = true;
                    step++;
                }
                else {
                    requirements->finances_project = false;
                    step++;
                }
            }
            else {
                fflush(stdin);
                check_print("Bad (yes//no) input, try one more time\n");
                continue;
            }
            break;
            }
        case 6:
            {
            check_print("Danger(yes//no):");
            if (check_bool_input(buffer)) {  // check input in fun
                if (is_true(buffer)) {
                    requirements->danger = true;
                    step++;
                }
                else {
                    requirements->danger = false;
                    step++;
                }
            }
            else {
                fflush(stdin);
                check_print("Bad (yes//no) input, try one more time\n");
                continue;
            }
            break;
            }
        default:
            {
            fflush(stdin);
            return false;
            }
        }
    }
    free(buffer);
    return true;
}

void printBool(bool isYes) {
    if (isYes){
        check_print("yes\n");
    }
    else{
        check_print("no\n");
    }
}

bool show_requirements(project_member *const requirements) {
    if(printf("========= Your requirements =========\nName:%s\nName:%s\nWork with project:",
           requirements->name,requirements->role) < 0)
        return false;
    printBool(requirements->work_with_project);
    check_print("Use project:");
    printBool(requirements->use_project);
    if(printf("Influence:%d\nFinances project:",requirements->influence) < 0)
        return false;
    printBool(requirements->finances_project);
    check_print("Danger:");
    printBool(requirements->danger);
    check_print("=====================================\n");
    return true;
}

answer * create_answer(size_t maxMemberSize) {
    answer * ans =(answer*)malloc(sizeof(answer));
    ans->size = 0;
    ans->arr_matches_count = (size_t *) calloc(maxMemberSize, sizeof(size_t));
    ans->arr_ptr = (project_member **) calloc(maxMemberSize, sizeof(project_member *));
    return ans;
}

void free_answer(answer * ans) {
    free(ans->arr_matches_count);
    free(ans->arr_ptr);
    ans->size = 0;
    free(ans);
}

bool equal_strings(char *const string1, char *const string2, size_t maxStringSize) {
    if (maxStringSize > MAX_INPUT_BUFFER)
        assert(false);
    size_t iter = 0;
    for (; string1[iter]!= '\0' || string2[iter] != '\0' ; iter++) {
        if (string1[iter] != string2[iter])
            return false;
    }
    if (string1[iter] != string2[iter])
        return false;
    return true;
}


bool find_snswer(project_member *const members, const size_t memberSize,
                project_member * requirements, answer * ans) {
    size_t matchesCount = 0;
    size_t matchesIter = 0;
    for (size_t memberIter = 0; memberIter < memberSize; memberIter++) {
        matchesCount = 0;
        if ( equal_strings(members[memberIter].name, requirements->name, MAX_INPUT_BUFFER))
            matchesCount++;
        if ( equal_strings( members[memberIter].role, requirements->role, MAX_INPUT_BUFFER))
            matchesCount++;
        if ( members[memberIter].work_with_project == requirements->work_with_project )
            matchesCount++;
        if ( members[memberIter].use_project == requirements->use_project )
            matchesCount++;
        if ( members[memberIter].influence == requirements->influence )
            matchesCount++;
        if ( members[memberIter].finances_project == requirements->finances_project )
            matchesCount++;
        if ( members[memberIter].danger == requirements->danger )
            matchesCount++;
        if(matchesCount == 0)
            continue;
        else {
            (ans->arr_ptr)[matchesIter] = &(members[memberIter]);
            ans->arr_matches_count[matchesIter++] = matchesCount;
            (ans->size)++;
        }
    }
    if (matchesIter == 0)
        return false;
    else
        return true;
}

void swap_size_t(size_t * a, size_t * b) {
    size_t temp = *a;
    *a = *b;
    *b = temp;
}

void swap_p_m(project_member ** a, project_member ** b) {
    project_member * temp = *a;
    *a = *b;
    *b = temp;
}

// reverse selection sort
size_t sort_for_output(answer * ans, const size_t memberIter) {
    size_t maxValue = ans->arr_matches_count[memberIter];
    size_t iterMaxValue = memberIter;
    for (size_t iter = memberIter + 1 ; iter < ans->size; iter++ ) {
        if (maxValue < (ans->arr_matches_count)[iter]){
            maxValue = (ans->arr_matches_count)[iter];
            iterMaxValue = iter;
        }
    }
    swap_p_m(&(ans->arr_ptr[memberIter]), &ans->arr_ptr[iterMaxValue]);
    swap_size_t(&ans->arr_matches_count[memberIter], &ans->arr_matches_count[iterMaxValue]);
    return maxValue;
}

void showAns(answer* ans) {
    check_print("============== Answer ===============\n");
    size_t matches = 0;
    for (size_t memberIter = 0; memberIter < ans->size; memberIter++){
        matches = sort_for_output(ans, memberIter);  // находит максимум совпадений для итератора
        if (matches < MIN_SHOW_MATCHES) {
            if (memberIter == 0)
                check_print("No elements for your requirements\n");
            return;
        }
        if(printf("Matched requirements:%lu\nName:%s\nRole:%s\nWork with project:",
                  ans->arr_matches_count[memberIter], ans->arr_ptr[memberIter]->name,
                  ans->arr_ptr[memberIter]->role) < 0)
            assert(false);
        printBool(ans->arr_ptr[memberIter]->work_with_project);
        check_print("Use project:");
        printBool(ans->arr_ptr[memberIter]->use_project);
        if(printf("Influence:%d\nFinance:",ans->arr_ptr[memberIter]->influence) < 0)
            assert(false);
        printBool(ans->arr_ptr[memberIter]->finances_project);
        check_print("Danger:");
        printBool(ans->arr_ptr[memberIter]->danger);
        check_print("=====================================\n");
    }
    check_print("============ End answer =============\n");
}
