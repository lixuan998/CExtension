#include "./Basic/include/cstring.h"
#include "./XML/include/xml.h"
#include "./Basic/include/cfile.h"

void test_phrase_xml()
{
    Xnode *root_node = create_xnode();
    Xnode *sub_node = create_xnode();
    XHeader *header;
    root_node -> node_name = create_cstring("testroot");
    insert_list(root_node -> attribute_keys, create_cstring("root_key"), APPEND);
    insert_list(root_node -> attribute_values, create_cstring("root_value"), APPEND);
    sub_node -> node_name = create_cstring("subnode");
    sub_node -> content = create_cstring("CONTENT");
    sub_node -> depth = 1;
    insert_list(sub_node -> attribute_keys, create_cstring("sub_node_key"), APPEND);
    insert_list(sub_node -> attribute_values, create_cstring("sub_node_value"), APPEND);
    insert_list(root_node -> childs, (void *)sub_node, APPEND);
    CString *xml_res = create_cstring(NULL);
    phrase_to_xml(header, root_node, xml_res);
    fwrite_all("/Users/climatex/Documents/Coding-Zone/Self_Projects/CExtension/res.xml", raw_cstring(xml_res));
}

void test_load_xml()
{
    char fpath[] = "/Users/climatex/Documents/Testing-Zone/test/word/document.xml";
    char *fcontent = fread_all(fpath);
    Xnode *root_node = NULL;
    XHeader *header = NULL;
    analyze_xml(&header, &root_node, fcontent);
    print_xml_tree(header, root_node);
}
int main()
{
    test_phrase_xml();
}