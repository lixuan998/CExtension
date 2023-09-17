#include "./Basic/include/cstring.h"
#include "./XML/include/xml.h"
#include "./Basic/include/cfile.h"

void test_phrase_xml()
{
    List *attr_keys = create_list();
    insert_list(attr_keys, (void *)create_cstring("attr1"), APPEND);
    List *attr_values = create_list();
    insert_list(attr_values, (void *)create_cstring("attr1_value"), APPEND);


    Xnode *root_node = create_xnode(FALSE, "root_node", NULL, attr_keys, attr_values);
    Xnode *sub_node = create_xnode(FALSE, "sub_node", NULL, attr_keys, attr_values);
    Xnode *header = create_xnode(TRUE, "header", NULL, attr_keys, attr_values);;
    
    add_child(root_node, sub_node);
    add_child(header, root_node);
    CString *xml_res = create_cstring(NULL);
    phrase_to_xml(header, xml_res);
    fwrite_all("/Users/climatex/Documents/Coding-Zone/Self_Projects/CExtension/res.xml", raw_cstring(xml_res));
}

void test_load_xml()
{
    char fpath[] = "/Users/climatex/Documents/Testing-Zone/test/word/fontTable.xml";
    char *fcontent = fread_all(fpath);
    Xnode *root_node = NULL;
    Xnode *header = NULL;
    analyze_xml(&root_node, fcontent);
    print_xml_tree(root_node);

    CString *res = create_cstring(NULL);
    phrase_to_xml(root_node, res);
    fwrite_all("/Users/climatex/Documents/Coding-Zone/Self_Projects/CExtension/res.xml", raw_cstring(res));
}
int main()
{
    test_load_xml();
//    test_phrase_xml(); 
}