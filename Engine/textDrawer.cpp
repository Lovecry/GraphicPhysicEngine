#include "textDrawer.h"


#include "SpriteBatch.h"
#include "SpriteFont.h"


using namespace utility;


TextFont::TextFont(ID3D11Device* device, const std::wstring spriteFontFileName)
	: mSpriteFont(nullptr)
{
	assert(device != nullptr);

	if(device != nullptr)
	{
		mSpriteFont = new DirectX::SpriteFont(device, spriteFontFileName.data());
	}
}

TextFont::~TextFont()
{
	delete mSpriteFont;
}

bool TextFont::isInitialized()
{
	return mSpriteFont != nullptr;
}


TextDrawer::TextDrawer(ID3D11DeviceContext* deviceContext)
	: mSpriteBatch(nullptr)
	, mCurrentPosition(DirectX::XMFLOAT2(10.0f, 10.0f))
	, mCurrentColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f))
	, mCurrentOrigin(DirectX::XMFLOAT2(0.0f, 0.0f))
	, mCurrentScale(DirectX::XMFLOAT2(1.0f, 1.0f))
	, mCurrentRotation(0.0f)
{
	assert(deviceContext != nullptr);
	if(deviceContext != nullptr)
	{
		mSpriteBatch = new DirectX::SpriteBatch(deviceContext);
	}
}

TextDrawer::~TextDrawer()
{
	delete mSpriteBatch;
}

void TextDrawer::beginDraw()
{
	mSpriteBatch->Begin();
}

void TextDrawer::endDraw()
{
	mSpriteBatch->End();
}

void TextDrawer::drawText(const TextFont& font, const std::wstring& text)
{
	DirectX::XMFLOAT4 zero(0.0f, 0.0f, 0.0f, 0.0f);
	font.mSpriteFont->DrawString(mSpriteBatch, text.data(), mCurrentPosition, DirectX::XMLoadFloat4(&mCurrentColor),
		mCurrentRotation, mCurrentOrigin, mCurrentScale);
}

void TextDrawer::setColor(const DirectX::XMFLOAT4& color)
{
	mCurrentColor = color;
}

void TextDrawer::setPosition(const DirectX::XMFLOAT2& position)
{
	mCurrentPosition = position;
}

void TextDrawer::setScale(const DirectX::XMFLOAT2& scale)
{
	mCurrentScale = scale;
}

void TextDrawer::setRotation(const float rotation, const DirectX::XMFLOAT2& origin)
{
	mCurrentRotation = rotation;
	mCurrentOrigin = origin;
}