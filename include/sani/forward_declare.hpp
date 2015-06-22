#pragma once

#define SANI_FORWARD_DECLARE(c) class c;
#define SANI_FORWARD_DECLARE_1(n1, c) namespace n1 { class c; }
#define SANI_FORWARD_DECLARE_2(n1, n2, c) namespace n1 { namespace n2 { class c; } }
#define SANI_FORWARD_DECLARE_3(n1, n2, n3, c) namespace n1 { namespace n2 { namespace n3 { class c; } } }
#define SANI_FORWARD_DECLARE_4(n1, n2, n3, n4, c) namespace n1 { namespace n2 { namespace n3 { namespace n4 { class c; } } } }