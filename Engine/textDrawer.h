#pragma once


#pragma comment(lib, "DirectXTK.lib")


#include <memory>
#include <d3d11.h>
#include <string>
#include <DirectXMath.h>


namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}


namespace utility
{
	class TextFont;

	class TextDrawer
	{
	public:
		TextDrawer(ID3D11DeviceContext* deviceContext);
		~TextDrawer();

		void setColor(const DirectX::XMFLOAT4& color);
		void setPosition(const DirectX::XMFLOAT2& position);
		void setScale(const DirectX::XMFLOAT2& scale);
		void setRotation(const float rotation, const DirectX::XMFLOAT2& origin);

		void beginDraw();
		void endDraw();
		void drawText(const TextFont& font, const std::wstring& text);

	private:
		TextDrawer(const TextDrawer&);
		TextDrawer operator=(const TextDrawer&);

		DirectX::SpriteBatch* mSpriteBatch;
		DirectX::XMFLOAT2 mCurrentPosition;
		DirectX::XMFLOAT4 mCurrentColor;
		DirectX::XMFLOAT2 mCurrentOrigin;
		DirectX::XMFLOAT2 mCurrentScale;
		float mCurrentRotation;
	};

	class TextFont
	{
	public:
		TextFont(ID3D11Device* device, const std::wstring spriteFontFileName);
		~TextFont();

		bool isInitialized();

	private:
		TextFont(const TextFont&);
		TextFont operator = (const TextFont&);

		DirectX::SpriteFont* mSpriteFont;

		friend class TextDrawer;
	};

}
