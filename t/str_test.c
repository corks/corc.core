#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "str.h"

START_TEST (test_raw_copy)
{
    char *in, *out;

    in = malloc(512);
    out = malloc(512);

    in = "Fish go moo, oh yes they do.";
    corcstr_copy_raw(out, in, 512);

    fail_if(strcmp(in, out) != 0,
            "Raw string copying failed: \"%s\"", out);
}
END_TEST

START_TEST (test_raw_concat)
{
    char *buf = malloc(512);
    
    buf = "Cheese ";
    corcstr_concat_raw(buf, "Fish go moo, oh yes they do.", 505);

    fail_if(strcmp(buf, "Cheese Fish go moo, oh yes they do.") != 0,
            "Raw string concatination failed: \"%s\"", buf);
}
END_TEST

START_TEST (test_corc_str_basics)
{
    CorcString *s;

    fail_if((s = corcstr_create()) == NULL,
            "corcstr_create() returned NULL");
    
    corcstr_append(s, "Fish go moo", 0);
    fail_if(strcmp(s->string, "Fish go moo") != 0,
            "0-len append failed: \"%s\"", s->string);

    corcstr_append(s, ", oh yes they do", 16);
    fail_if(strcmp(s->string, "Fish go moo, oh yes they do") != 0,
            "Specified-length append failed: \"%s\"", s->string);

    corcstr_append_char(s, '.');
    fail_if(strcmp(s->string, "Fish go moo, oh yes they do.") != 0,
            "Single-character append failed: \"%s\"", s->string);
}
END_TEST

START_TEST (test_corc_str_alias)
{
    CorcString *s;

    s = corcstr("Fish go moo, oh yes they do.");
    fail_if(s == NULL,
            "corcstr() returned NULL");
    fail_if(strcmp(s->string, "Fish go moo, oh yes they do.") != 0,
            "corcstr() alias failed: \"%s\"", s->string);
}
END_TEST

START_TEST (test_corc_str_resize)
{
    CorcString *s;

    s = corcstr_create();
    fail_if(s == NULL,
            "corcstr_create() returned NULL");
    fail_unless(s->size == 64,
            "corcstr default size incorrect");
    
    corcstr_append(s, "Moo.", 0);
    fail_if(strcmp(s->string, "Moo.") != 0,
            "corcstr_append() failed: \"%s\"", s->string);
    fail_unless(s->size == 64,
            "corcstr size changed unexpectedly");

    corcstr_resize(s, 128);
    fail_if(strcmp(s->string, "Moo.") != 0,
            "String modified upon resize");
    fail_unless(s->size == 128,
            "corcstr size changed incorrectly");
}
END_TEST

START_TEST (test_corc_str_clear)
{
    CorcString *s;

    s = corcstr("Fish go moo, oh yes they do.");
    fail_if(strcmp(s->string, "Fish go moo, oh yes they do.") != 0,
            "corcstr() failed to create string correctly: \"%s\"", s->string);

    corcstr_clear(s);
    fail_unless(*s->string == '\0',
            "corcstr_clear() failed to nullify string");
    fail_unless(*s->string == *s->end,
            "corcstr_clear() failed to reset string end");
}
END_TEST

Suite * corc_str_suite(void)
{
    Suite *s = suite_create("libcorc.core");
    TCase *tc_str = tcase_create("String");
    
    tcase_add_test(tc_str, test_raw_copy);
    tcase_add_test(tc_str, test_raw_concat);
    tcase_add_test(tc_str, test_corc_str_basics);
    tcase_add_test(tc_str, test_corc_str_alias);
    tcase_add_test(tc_str, test_corc_str_resize);
    tcase_add_test(tc_str, test_corc_str_clear);

    suite_add_tcase(s, tc_str);

    return s;
}

int main(void)
{
    int failed;
    Suite *s = corc_str_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    printf("Failed %d tests.\n", failed);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
