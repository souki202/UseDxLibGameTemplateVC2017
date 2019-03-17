#pragma once
#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include "RefCounter.h"
#include "DxLib.h"
#include "Align.h"
#include "CommonSettings.h"
#include "NowLoadingWindow.h"

#undef max
#undef min

class Image {
public:
	Image();
	Image(std::string filePath);
	Image(std::string filePath, const Point& position);
	Image(const int& handle);
	Image(int&& handle);
	Image(const int& handle, const Point& position);

	Image(const Image& rhs) { operator=(std::forward<const Image>(rhs)); };
	Image(Image&& rhs) { operator=(std::forward<Image>(rhs)); };
	Image& operator=(const Image& rhs);
	Image& operator=(Image&& rhs);

	~Image();

	void init();

	void setAlign(const Align::Horizontal& hAlign) { setAlign(hAlign, vAlign); };
	void setAlign(const Align::Vertical& vAlign) { setAlign(hAlign, vAlign); };
	void setAlign(const Align::Horizontal& hAlign, const Align::Vertical& vAlign);
	void setImage(std::string filePath);
	void setImage(const int& handle);
	void setImage(int&& handle); //画像のリソース破棄はImage内で実行される
	void setPosition(float x, float y) { setPosition(std::make_pair(x, y)); };
	void setPosition(const Point& position);
	void setScrollPosition(float x, float y) { setScrollPosition(std::make_pair(x, y)); };
	void setScrollPosition(const Point& scroll);
	void setScale(float x, float y) { setScale(std::make_pair(x, y)); };
	void setScale(const Point& scale);
	void setAngle(float angle);
	void addAngle(float delta) { setAngle(angle + delta); };
	void setAlpha(int alpha) { this->alpha = alpha; }; //0~255
	void recalcPosition();

	const int& getHandle() const { return img; };
	const Point& getPosition() { if (rawSize.first <= 0) calcImageSize(); return rawPos; };
	const Point& getUpperLeftPosition() { if (rawSize.first <= 0) calcImageSize();  return pos; };
	const std::array<std::pair<float, float>, 4>& getVertexes() const { return vertexes; };
	Point getPositionNonScroll() { return std::make_pair(pos.first - scrollPos.first, pos.second - scrollPos.second); };
	const Point& getImageSize() { if (rawSize.first <= 0) calcImageSize();  return rawSize; }; //画像そのままのサイズを返します
	const Point& getSize() { if (rawSize.first <= 0) calcImageSize(); return scaledSize; }; //画像をリスケール後のサイズを返します
	const float& getAngle() const { return angle; };

	virtual void draw();
	void drawByVertex(const std::vector<Point>& vertex) const; //頂点の値は保存されない
	virtual void update();

	void setHasDefaultCollider(bool b) { hasDefaultCollider = b; };

	bool getIsOutOfWindow();
	void calcImageSize();

	void setIsPremulti(bool b) { isPremulti = b; };
protected:

private:
	bool isExternal = false;
	int img;
	std::pair<float, float> rawPos = std::make_pair(0.f, 0.f);
	std::pair<float, float> pos = std::make_pair(0.f, 0.f);

	std::pair<float, float> scrollPos = std::make_pair(0.f, 0.f);
	std::array<std::pair<float, float>, 4> vertexes;

	std::pair<float, float> rawSize = std::make_pair(0.f, 0.f);
	std::pair<float, float> scaledSize = std::make_pair(0.f, 0.f);
	std::pair<float, float> scale = std::make_pair(1.f, 1.f);

	float angle = 0.f;
	int alpha;

	Align::Horizontal hAlign = Align::Horizontal::LEFT;
	Align::Vertical vAlign = Align::Vertical::UPPER;
	bool hasDefaultCollider = true;
	bool isPremulti = false;

	std::shared_ptr<RefCounter> counter; //ムーブされた場合は抜け殻になる.
};