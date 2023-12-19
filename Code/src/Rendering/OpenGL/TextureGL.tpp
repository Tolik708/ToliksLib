#ifndef TEXTURE_GL_TPP
#define TEXTURE_GL_TPP

namespace Tolik
{
template<std::size_t Index, typename... Args>
void TextureGL::SetParametrs(const std::tuple<Args...> &textureParameters) const
{
  // Clamp is important because compiler looks ahead and gives errors
  if constexpr(Index != sizeof...(Args) - 1)
		Print<std::clamp(Index + 1, static_cast<std::size_t>(1), sizeof...(Args) - 1)>(t);

  SetParametr(std::get<0>(std::get<Index>(textureParametrs)), std::get<1>(std::get<Index>(textureParametrs)));
}

template<>
inline void TextureGL::SetParametr<int>(uint32_t parametrName, int parametr)
{
  GL_CALL(glTexParameteri(m_textureType, parametrName, parametr));
}

template<>
inline void TextureGL::SetParametr<float>(uint32_t parametrName, float parametr)
{
  GL_CALL(glTexParameterf(m_textureType, parametrName, parametr));
}

template<>
inline void TextureGL::SetParametr<int*>(uint32_t parametrName, int *parametr)
{
  GL_CALL(glTexParameteriv(m_textureType, parametrName, parametr));
}

template<>
inline void TextureGL::SetParametr<float*>(uint32_t parametrName, float *parametr)
{
  GL_CALL(glTexParameterfv(m_textureType, parametrName, parametr));
}

template<>
inline void TextureGL::SetParametr<const int*>(uint32_t parametrName, const int *parametr)
{
  GL_CALL(glTexParameterIiv(m_textureType, parametrName, parametr));
}

template<>
inline void TextureGL::SetParametr<const uint32_t*>(uint32_t parametrName, const float *parametr)
{
  GL_CALL(glTexParameterIuiv(m_textureType, parametrName, parametr));
}
}

#endif