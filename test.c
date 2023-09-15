#include "./Basic/include/cstring.h"
#include "./XML/include/xml.h"

int main()
{
    char test_arr[] = "<根>   <main val = \"testval\" key = \"value\"><!-- this is a comment --><c><d/><t/></c><a></a></main><test><b></b></test></根>";
    analyze_xml(test_arr);
    test();
}