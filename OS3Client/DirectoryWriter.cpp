#include "stdafx.h"
#include "DirectoryWriter.h"
DirectoryWriter::DirectoryWriter(void)
{
}


DirectoryWriter::~DirectoryWriter(void)
{
}

void Direc
//
//void DirectoryWriter::InitList()
//{
//	boost::property_tree::ptree root;
//	boost::property_tree::ptree version;
//	boost::property_tree::ptree filesnode;
//	version.put("version",1);
//	root.add_child("filesystem",version);
//
//	using namespace boost::filesystem;
//    recursive_directory_iterator dir("/mapje"), end;
//    while (dir != end)
//    {
//		if(!is_directory(dir->path()))
//		{
//			boost::property_tree::ptree node;
//			
//			node.put("filename",dir->path().filename());
//			node.put("directory",dir->path());
//			filesnode.add_child("file", node);
//		}
//        ++dir;
//    }
//	root.add_child("filesystem.files",filesnode);
//	boost::property_tree::write_xml("config.xml", root);
//}
//
//bool DirectoryWriter::CheckNodeExists(const std::string key, const std::string value)
//{
//	boost::property_tree::ptree pt;
//    boost::property_tree::xml_parser::read_xml("config.xml", pt);
//
//    try {
//        pt.get_child(key);
//    }
//    catch(boost::exception &ex)
//    {  
//        return false;
//    }
//
//    if(remove)
//    {  
//        boost::property_tree::ptree newPt;
//
//        BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child(key))
//        {  
//            if(v.second.data() == value)
//                return true;
//        }
//	}
//	return false;;
//}
//
//void DirectoryWriter::traverseTree(const boost::property_tree::ptree& pt, std::string key,std::string node)
//{
//	std::string nkey;
//	
//	if (!key.empty())
//	{
//		std::cout << pt.data()<< std::endl;
//		nkey = key + ".";
//
//		if (pt.data()==node)
//		{
//			//pt.erase(key);
//		}
//	}
//	
//	boost::property_tree::ptree::const_iterator end = pt.end();
//	
//	for ( boost::property_tree::ptree::const_iterator it = pt.begin(); it != end; ++it)
//	{
//		traverseTree(it->second, nkey + it->first,node);
//	}
//}
//
//////
//void DirectoryWriter::WriteNode(char *nodeName,char*directory)
//{
//	boost::property_tree::ptree root, file;
//	boost::property_tree::read_xml("config.xml", root);
//
//	file.put("file.filename",nodeName);
//	file.put("file.directory",directory);
//
//	root.insert(root.get_child("filesystem.files").end(),file.front());
//
//	boost::property_tree::xml_writer_settings<char> set(' ', 4);
//	write_xml("config.xml", root, std::locale(), set);
//}
//
//void DirectoryWriter::UpdateNode(char*nodeName,char *renamename)
//{
//	boost::property_tree::ptree tree;
//	boost::property_tree::read_xml("config.xml", tree);
//	traverseTree(tree,"filesystem",nodeName);
//	BOOST_FOREACH(boost::property_tree::ptree::value_type &v,tree.get_child("filesystem.files"))
//	{
//		std::cout << v.first.data() << std::endl;
//	}
//
//}
//
//void DirectoryWriter::DeleteNode(const std::string key, const std::string value)
//{
//	boost::property_tree::ptree tree;
//	boost::property_tree::read_xml("config.xml", tree);
//	auto &children = tree.get_child("filesystem.files.file");
//	for(auto &attrIt = children.begin(); attrIt != children.end();)
//	{
//	  auto &attr = *attrIt;
//
//	  if (attr.first.data()==value)
//	  {
//		  attrIt = children.erase(attrIt);
//	  }else 
//		  ++attrIt;
//	}
//}
//
//
