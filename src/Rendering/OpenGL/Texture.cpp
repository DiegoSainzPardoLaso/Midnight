#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture *fTextureOpenGL::Load(std::vector<const char *>& paths, bool flipY)
{
	Texture* textures = new Texture[paths.size()];

	stbi_set_flip_vertically_on_load(flipY);

	for (size_t i = 0; i < paths.size(); i++)
	{
		// Load texture
		unsigned char* data = (unsigned char *)stbi_load(paths.at(i), &textures[i].width, &textures[i].height, &textures[i].channels, 0);
	
		if (data)
		{
			// Gen Texture handle
			glGenTextures(1, &textures[i].id);
			// Bind texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);

			// @note parameterize this things
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,	  GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,	  GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);


			if (textures[i].channels > 3) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i].width, textures[i].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); }
			else						  { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  textures[i].width, textures[i].height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data);	}

			glGenerateMipmap(GL_TEXTURE_2D);

			// Free pixels data
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to Load Texture [ " << paths.at(i) << " ]" << '\n';
		}
	}


	return textures;
}

Texture *fTextureOpenGL::Load(const char *path, bool flipY)
{
	Texture* texture = reinterpret_cast<Texture*>(malloc(sizeof(Texture)));

	stbi_set_flip_vertically_on_load(flipY);

	// Load texture
	unsigned char* data = (unsigned char *)stbi_load(path, &texture->width, &texture->height, &texture->channels, 0);

	if (data)
	{
		// Gen Texture handle
		glGenTextures(1, &texture->id);
		// Bind texture
		glBindTexture(GL_TEXTURE_2D, texture->id);

		// @note parameterize this things
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

		if (texture->channels > 3) { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); }
		else					   { glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  texture->width, texture->height, 0, GL_RGB,  GL_UNSIGNED_BYTE, data); }

		glGenerateMipmap(GL_TEXTURE_2D);

		// Free pixels data
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to Load Texture [ " << path << " ]" << '\n';
	}

	return texture;

}