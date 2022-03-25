#include "../defines.h"

class FileManager
{
	class FileManager_singleton
	{
	public:

		///////////////////////////////////////////////////////////////
		/// FILE CONSTANT
		///
		/// Directory with resources
		const std::string FOLDER_WITH_RESOURCES = "ResDir";
		///
		/// Directory with logs
		const std::string FOLDER_WITH_LOGS = "LogDir";
		///
		/// Project folder name
		const std::string FOLDER_WITH_SOURCE = "Simple2dStrilalka";
		///////////////////////////////////////////////////////////////

		
		FileManager_singleton()
		{
			fs::path path_to_bin = fs::current_path();
			fs::path path_to_resources;

			
			// Init the res path
			auto path_to_res_in_bin_dir = fs::current_path();
			path_to_res_in_bin_dir.append(FOLDER_WITH_RESOURCES);
			if (!fs::is_directory(path_to_res_in_bin_dir))
				fs::create_directory(path_to_res_in_bin_dir);


			// Init the files in res folder
			bool if_in_build_dir = false;
			for (auto i : fs::current_path())
			{
				path_to_resources.append(i.string());
				if (i.string() == FOLDER_WITH_SOURCE)
				{
					if_in_build_dir = true;
					break;
				}
			} if(!if_in_build_dir) goto IF_NOT_IN_BUILD_DIR;

			
			// Copy files from src folder to bin folder
			path_to_resources.append(FOLDER_WITH_RESOURCES);
			path_to_resources.append(".");
			fs::copy(path_to_resources,
				path_to_res_in_bin_dir,
				fs::copy_options::recursive | fs::copy_options::overwrite_existing
			);


			IF_NOT_IN_BUILD_DIR: {}	
		}
		~FileManager_singleton() = default;
	};

	static std::shared_ptr<FileManager_singleton> fm_singleton;
public:

	static std::string getResFile(const std::string& file_name)
	{
		return fm_singleton->FOLDER_WITH_RESOURCES + "\\"s + file_name;
	}

	static std::string getLogFile(const std::string& file_name)
	{
		return fm_singleton->FOLDER_WITH_LOGS + "\\"s + file_name;
	}
};


inline std::shared_ptr<FileManager::FileManager_singleton>
FileManager::fm_singleton
= std::make_shared<FileManager::FileManager_singleton>();




