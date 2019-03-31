#pragma once
#include "SceneBaseObject.h"
#include "mat4.h"
#include "Image.h"
#include "BMPParser.h"
#include "JpegParser.h"
#include "AssetLoadManager.h"

namespace Phantom {
    class SceneObjectTexture : public SceneBaseObject
    {
        protected:
            std::string m_Name;
            uint32_t m_nTexCoordIndex;
            std::shared_ptr<Image> m_pImage;
            std::vector<Phantom::maths::mat4x4> m_Transforms;

        public:
            SceneObjectTexture() : SceneBaseObject(SceneObjectType::kSceneObjectTypeTexture), m_nTexCoordIndex(0) {};
            SceneObjectTexture(const std::string& name) : SceneBaseObject(SceneObjectType::kSceneObjectTypeTexture), m_Name(name), m_nTexCoordIndex(0) {};
            SceneObjectTexture(uint32_t coord_index, std::shared_ptr<Image>& image) : SceneBaseObject(SceneObjectType::kSceneObjectTypeTexture), m_nTexCoordIndex(coord_index), m_pImage(image) {};
            SceneObjectTexture(uint32_t coord_index, std::shared_ptr<Image>&& image) : SceneBaseObject(SceneObjectType::kSceneObjectTypeTexture), m_nTexCoordIndex(coord_index), m_pImage(std::move(image)) {};
            SceneObjectTexture(SceneObjectTexture&) = default;
            SceneObjectTexture(SceneObjectTexture&&) = default;
            void AddTransform(Phantom::maths::mat4x4& matrix) { m_Transforms.push_back(matrix); };
            void SetName(const std::string& name) { m_Name = name; };
            void SetName(std::string&& name) { m_Name = std::move(name); };
            const std::string& GetName() const { return m_Name; };
            void LoadTexture() {
                if (!m_pImage)
                {
                    // we should lookup if the texture has been loaded already to prevent
                    // duplicated load. This could be done in Asset Loader Manager.
                    Buffer buf = g_pAssetLoader->SyncOpenAndReadBinary(m_Name.c_str());
					if (buf.GetDataSize() <= 0)
					{
						return;
					}
                    std::string ext = m_Name.substr(m_Name.find_last_of("."));
					//µ÷ÊÔb/w
                    /*if (ext == ".bmp")
                    {
                        BmpParser bmp_parser;
                        m_pImage = std::make_shared<Image>(bmp_parser.Parse(buf));
					}
					else if (ext == ".jpg")
					{
						JpegParser jpeg_parser;
						m_pImage = std::make_shared<Image>(jpeg_parser.Parse(buf));
					}
					else {*/
						//assert(); //Ìæ»»Ä¬ÈÏÕÕÆ¬
						buf = g_pAssetLoader->SyncOpenAndReadBinary("Textures/b.jpg");
						JpegParser jpeg_parser;
						m_pImage = std::make_shared<Image>(jpeg_parser.Parse(buf));
					//}
                }
            }
        

            std::shared_ptr<Image> GetTextureImage()
            { 
                if (!m_pImage)
                {
                    LoadTexture();
                }

                //AdjustTextureBitcount();

                return m_pImage; 
            };

        friend std::ostream& operator<<(std::ostream& out, const SceneObjectTexture& obj);
    };
}
