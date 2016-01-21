#include "minunit.h"
#include "bstrlib.h"

char *test_bfromcstr() {
    char *str = "Hello, World";
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    mu_assert(b->data[0] == str[0], "bstring data first char should be the same");
    mu_assert(b->data[6] == str[6], "bstring data sixth char should be the same");

    bdestroy(b);

    return NULL;
}

char *test_blk2bstr() {
    char *str = "Hello, World";
    bstring b = blk2bstr(str, 8);
    mu_assert(b != NULL, "blk2bstr failed");
    mu_assert(b->data[0] == str[0], "bstring data first char should be the same");
    mu_assert(b->data[6] == str[6], "bstring data sixth char should be the same");

    bdestroy(b);

    return NULL;
}

char *test_bstrcpy() {
    bstring b1 = bfromcstr("Hello, World");
    bstring b2 = bstrcpy(b1);
    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bstrcpy failed");
    mu_assert(b1->data[0] == b2->data[0], "bstring data first char should be the same");
    mu_assert(b1->data[6] == b2->data[6], "bstring data sixth char should be the same");

    bdestroy(b1);
    bdestroy(b2);

    return NULL;
}

char *test_bassign() {
    bstring b1 = bfromcstr("Hello, World");
    bstring b2 = bfromcstr("FOO BAR BAZ");
    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bfromcstr failed");
    mu_assert(b1->data[0] != b2->data[0], "bstring data first char should not be the same");
    mu_assert(b1->data[6] != b2->data[6], "bstring data sixth char should not be the same");

    int err = bassign(b1, b2);
    mu_assert(err == 0, "no error should be returned");

    mu_assert(b1->data[0] == b2->data[0], "bstring data first char should be the same");
    mu_assert(b1->data[6] == b2->data[6], "bstring data sixth char should be the same");

    bdestroy(b1);
    bdestroy(b2);

    return NULL;
}

char *test_bassigncstr() {
    char *str = "FOO BAR BAZ";
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    mu_assert(b->data[0] != str[0], "bstring data first char should not be the same");
    mu_assert(b->data[6] != str[6], "bstring data first char should not be the same");

    int err = bassigncstr(b, str);
    mu_assert(err == 0, "no error should be returned");

    mu_assert(b->data[0] == str[0], "bstring data first char should be the same");
    mu_assert(b->data[6] == str[6], "bstring data first char should be the same");

    bdestroy(b);

    return NULL;
}

char *test_bassignblk() {
    char *str = "FOO BAR BAZ";
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    mu_assert(b->data[0] != str[0], "bstring data first char should not be the same");
    mu_assert(b->data[6] != str[6], "bstring data first char should not be the same");

    int err = bassignblk(b, str, 8);
    mu_assert(err == 0, "no error should be returned");

    mu_assert(b->data[0] == str[0], "bstring data first char should be the same");
    mu_assert(b->data[6] == str[6], "bstring data first char should be the same");

    bdestroy(b);

    return NULL;
}

char *test_bdestroy() {
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    int err = bdestroy(b);
    mu_assert(err != BSTR_ERR, "no error should be returned");

    return NULL;
}

char *test_bconcat() {
    bstring b1 = bfromcstr("Hello,");
    bstring b2 = bfromcstr("World");
    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bfromcstr failed");
    int err = bconcat(b1, b2);
    mu_assert(err == 0, "no error should be returned");

    mu_assert(b1->data[6] == b2->data[0], "b1 data fifth char should be the same as b2 first char");
    mu_assert(b1->data[8] == b2->data[2], "b1 data seventh char should be the same as b2 third char");
    bdestroy(b1);
    bdestroy(b2);

    return NULL;
}

char *test_bstricmp() {
    bstring b1 = bfromcstr("HELLO");
    bstring b2 = bfromcstr("HELLO");
    bstring b3 = bfromcstr("hello");
    bstring b4 = bfromcstr("World");

    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bfromcstr failed");
    mu_assert(b3 != NULL, "bfromcstr failed");
    mu_assert(b4 != NULL, "bfromcstr failed");

    int cmp1 = bstricmp(b1, b2);
    mu_assert(cmp1 == 0, "bstrings are the same");
    int cmp2 = bstricmp(b1, b3);
    mu_assert(cmp2 == 0, "bstrings are the same");
    int cmp3 = bstricmp(b1, b3);
    mu_assert(cmp3 != 1, "bstrings are not the same");

    bdestroy(b1);
    bdestroy(b2);
    bdestroy(b3);
    bdestroy(b4);
    return NULL;
}

char *test_biseq() {
    bstring b1 = bfromcstr("HELLO");
    bstring b2 = bfromcstr("HELLO");
    bstring b3 = bfromcstr("hello");

    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bfromcstr failed");
    mu_assert(b3 != NULL, "bfromcstr failed");

    int cmp1 = biseq(b1, b2);
    mu_assert(cmp1 == 1, "bstrings are the same");
    int cmp2 = bstricmp(b1, b3);
    mu_assert(cmp2 == 0, "bstrings are not the same");

    bdestroy(b1);
    bdestroy(b2);
    bdestroy(b3);
    return NULL;
}

char *test_binstr() {
    bstring b1 = bfromcstr("foo bar baz");
    bstring b2 = bfromcstr("bar");
    mu_assert(b1 != NULL, "bfromcstr failed");
    mu_assert(b2 != NULL, "bfromcstr failed");

    int cmp1 = binstr(b1, 0, b2);
    mu_assert(cmp1 == 4, "b2 is at pos 5 in b1");
    int cmp2 = binstr(b1, 6, b2);
    mu_assert(cmp2 == BSTR_ERR, "b2 is not found in b1");

    bdestroy(b1);
    bdestroy(b2);

    return NULL;
}

char *test_bfindreplace() {
    bstring b1       = bfromcstr("foo bar baz");
    bstring find     = bfromcstr("bar");
    bstring replace  = bfromcstr("BAR");
    bstring expected = bfromcstr("foo BAR baz");
    mu_assert(b1       != NULL, "bfromcstr failed");
    mu_assert(find     != NULL, "bfromcstr failed");
    mu_assert(replace  != NULL, "bfromcstr failed");
    mu_assert(expected != NULL, "bfromcstr failed");

    int err = bfindreplace(b1, find, replace, 0);
    mu_assert(err != BSTR_ERR, "error whilst findreplace");
    int cmp = biseq(b1, expected);
    mu_assert(cmp == 1, "b1 is not the same as expected");

    bdestroy(b1);
    bdestroy(find);
    bdestroy(replace);
    bdestroy(expected);

    return NULL;
}

char *test_bsplit() {
    bstring b1 = bfromcstr("foo bar baz");
    mu_assert(b1 != NULL, "bfromcstr failed");

    bstring ex1 = bfromcstr("foo");
    mu_assert(ex1 != NULL, "bfromcstr failed");
    bstring ex2 = bfromcstr("bar");
    mu_assert(ex2 != NULL, "bfromcstr failed");
    bstring ex3 = bfromcstr("baz");
    mu_assert(ex3 != NULL, "bfromcstr failed");

    struct bstrList *list = bsplit(b1, bchar(b1, 3));

    int cmp1 = biseq(list->entry[0], ex1);
    mu_assert(cmp1 == 1, "first split is not the same as ex1");
    int cmp2 = biseq(list->entry[1], ex2);
    mu_assert(cmp2 == 1, "second split is not the same as ex2");
    int cmp3 = biseq(list->entry[2], ex3);
    mu_assert(cmp3 == 1, "third split is not the same as ex3");

    bdestroy(b1);
    bdestroy(ex1);
    bdestroy(ex2);
    bdestroy(ex3);

    bstrListDestroy(list);

    return NULL;
}

char *test_bformat() {
    bstring b1 = bformat("%d %s", 3, "foo");
    mu_assert(b1 != NULL, "bfromcstr failed");
    bstring expected = bfromcstr("3 foo");
    mu_assert(expected != NULL, "bfromcstr failed");

    int cmp = biseq(b1, expected);
    mu_assert(cmp == 1, "b1 is not the same as expected");

    bdestroy(b1);
    bdestroy(expected);
    return NULL;
}

char *test_blength() {
    bstring b1 = bfromcstr("foo bar baz");
    mu_assert(b1 != NULL, "bfromcstr failed");
    int len = blength(b1);
    mu_assert(len == 11, "length should be 11");
    return NULL;
}

char *test_bdata() {
    char *str = "Hello, World";
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    mu_assert(bdata(b)[0] == str[0], "bstring data first char should be the same");
    mu_assert(bdata(b)[6] == str[6], "bstring data sixth char should be the same");

    bdestroy(b);

    return NULL;
}

char *test_bchar() {
    char *str = "Hello, World";
    bstring b = bfromcstr("Hello, World");
    mu_assert(b != NULL, "bfromcstr failed");
    char c1 = bchar(b, 0);
    char c2 = bchar(b, 6);
    mu_assert(c1 == str[0], "bstring data first char should be the same");
    mu_assert(c2 == str[6], "bstring data sixth char should be the same");

    bdestroy(b);

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_bstrcpy);
    mu_run_test(test_bassign);
    mu_run_test(test_bassigncstr);
    mu_run_test(test_bassignblk);
    mu_run_test(test_bdestroy);
    mu_run_test(test_bconcat);
    mu_run_test(test_bstricmp);
    mu_run_test(test_biseq);
    mu_run_test(test_binstr);
    mu_run_test(test_bfindreplace);
    mu_run_test(test_bsplit);
    mu_run_test(test_bformat);
    mu_run_test(test_blength);
    mu_run_test(test_bdata);
    mu_run_test(test_bchar);

    return NULL;
}

RUN_TESTS(all_tests);
