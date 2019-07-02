#include "common/AssetLoadManager.h"

#include "graphics/Image.h"
#include "parser/BMPParser.h"
#include "parser/JpegParser.h"
#include "common/utility.hpp"
#include "OpenGEX.h"
#include "common/BehaviourManager.h"



namespace Phantom {


	class TestBehaviour :public BehaviourManager
	{
	public:
		virtual int Init();
		virtual void Shutdown() {};
		virtual void Tick() { BehaviourManager::Tick(); };
	protected:
	private:
	};

	int TestBehaviour::Init()
	{
		std::shared_ptr<Image> m_pImage;
		std::string  m_Name = "Textures/len_full.jpg";
		Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary(m_Name.c_str());
		std::string ext = m_Name.substr(m_Name.find_last_of("."));
		if (ext == ".bmp")
		{
			BmpParser bmp_parser;
			m_pImage = std::make_shared<Image>(bmp_parser.Parse(buf));
		}
		else if(ext == ".jpg")
		{
			/*JpegParser jpeg_parser;
			m_pImage = std::make_shared<Image>(jpeg_parser.Parse(buf));*/
		}
		else {
		}

		return 0;
	}
	BehaviourManager*     g_pBehaviourManager = static_cast<BehaviourManager*>(new TestBehaviour);
}

