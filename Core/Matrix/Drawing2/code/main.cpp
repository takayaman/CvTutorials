/*=============================================================================
 * Project : Drawing2
 * Code : main.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/12/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * 描画関数を用いた図形描画
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <stdint.h>
#include <glog/logging.h>

#include <opencv2/opencv.hpp>

#include <string>

/*=== Local Define / Local Const ============================================*/
static const int32_t kDefAnimFrameNum = 100; /**< 各プリミティブを描画するフレーム数 */
static const int32_t kDefDelay = 5;     /**< 一個のプリミティブを描画後の待ち時間(msec) */

static const int32_t kDefWindowWidth = 900; /**< ウィンドウ幅 */
static const int32_t kDefWindowHeight = 600; /**< ウィンドウ高さ */

/*=== Local Variable ========================================================*/
static int32_t x_1 = -kDefWindowWidth / 2; /**< 乱数の下限X */
static int32_t x_2 = kDefWindowWidth * 3 / 2; /**< 乱数の上限X */
static int32_t y_1 = -kDefWindowWidth / 2; /**< 乱数の下限Y */
static int32_t y_2 = kDefWindowWidth * 3 / 2; /**< 乱数の上限Y */


/*=== Local Function Define =================================================*/
/** ランダムに色を生成
 * @param rng 乱数発生器
 * @return BGR色値
 */
cv::Scalar RandomColor(cv::RNG &rng);

/** ランダムに線分を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomLines(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムに矩形を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomRectangles(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムに楕円を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomEllipses(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムにポリゴン(ワイヤ)を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomPolylines(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムにポリゴン(塗りつぶし)を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomFilledPolygons(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムに円のを描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DrawRandomCircles(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** ランダムな位置にテキストを描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DisplayRandomText(cv::Mat &image, std::string windowname, cv::RNG &rng);

/** デモ終了文字を描画
 * @param image 描画画像
 * @param windowname 描画先ウィンドウ名
 * @param rng 乱数発生器
 * @return true : キーが押された, false : 何も押されてない
 */
bool DisplayBigEnd(cv::Mat &image, std::string windowname);

/*=== Local Function Implementation =========================================*/
cv::Scalar RandomColor(cv::RNG &rng) {
  int32_t color = static_cast<uint32_t>(rng);
  int32_t blue = color & 255; // colorの下位8bit
  int32_t green = (color >> 8) & 255; // colorの中央8bit
  int32_t red = (color >> 16) & 255; // colorの上位8bit
  return cv::Scalar(blue, green, red);
}

bool DrawRandomLines(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  cv::Point point0, point1;
  for(int32_t i = 0; i < kDefAnimFrameNum; i++) {
    point0.x = rng.uniform(x_1, x_2);
    point0.y = rng.uniform(x_1, y_2);
    point1.x = rng.uniform(x_1, x_2);
    point1.y = rng.uniform(y_1, y_2);
    cv::line(image, point0, point1, RandomColor(rng), rng.uniform(1, 10), 8);
    cv::imshow(windowname, image);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

bool DrawRandomRectangles(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  cv::Point point0, point1;
  int32_t linetype = 8;
  int32_t thickness = rng.uniform(-3, 10);
  for(int32_t i = 0; i < kDefAnimFrameNum; i++) {
    point0.x = rng.uniform(x_1, x_2);
    point0.y = rng.uniform(x_1, y_2);
    point1.x = rng.uniform(x_1, x_2);
    point1.y = rng.uniform(y_1, y_2);
    cv::rectangle(image, point0, point1, RandomColor(rng), MAX(thickness, -1),
                  linetype);
    cv::imshow(windowname, image);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

bool DrawRandomEllipses(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  int32_t linetype = 8;
  for(int32_t i = 0; i < kDefAnimFrameNum; i++) {
    cv::Point center;
    center.x = rng.uniform(x_1, x_2);
    center.y = rng.uniform(y_1, y_2);
    cv::Size axes;
    axes.width = rng.uniform(0, 200);
    axes.height = rng.uniform(0, 200);
    double_t angle = rng.uniform(0, 180);
    cv::RotatedRect rotatedrect = cv::RotatedRect(center, axes, angle);
    cv::ellipse(image, rotatedrect, RandomColor(rng), rng.uniform(-1, 9),
                linetype);
    cv::imshow(windowname, image);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

bool DrawRandomPolylines(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  int32_t linetype = 8;
  for(int32_t i = 0; i < kDefAnimFrameNum; i++) {
    cv::Point points[2][3];
    points[0][0].x = rng.uniform(x_1, x_2);
    points[0][0].y = rng.uniform(y_1, y_2);
    points[0][1].x = rng.uniform(x_1, x_2);
    points[0][1].y = rng.uniform(y_1, y_2);
    points[0][2].x = rng.uniform(x_1, x_2);
    points[0][2].y = rng.uniform(y_1, y_2);
    points[1][0].x = rng.uniform(x_1, x_2);
    points[1][0].y = rng.uniform(y_1, y_2);
    points[1][1].x = rng.uniform(x_1, x_2);
    points[1][1].y = rng.uniform(y_1, y_2);
    points[1][2].x = rng.uniform(x_1, x_2);
    points[1][2].y = rng.uniform(y_1, y_2);
    const cv::Point* p_points[2] = {points[0], points[1]};
    int32_t numpoints[] = {3, 3};
    cv::polylines(image, p_points, numpoints, 2, true, RandomColor(rng),
                  rng.uniform(1,10), linetype);
    cv::imshow(windowname, image);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

bool DrawRandomFilledPolygons(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  int32_t linetype = 8;
  for ( int i = 0; i < kDefAnimFrameNum; i++ ) {
    cv::Point points[2][3];
    points[0][0].x = rng.uniform(x_1, x_2);
    points[0][0].y = rng.uniform(y_1, y_2);
    points[0][1].x = rng.uniform(x_1, x_2);
    points[0][1].y = rng.uniform(y_1, y_2);
    points[0][2].x = rng.uniform(x_1, x_2);
    points[0][2].y = rng.uniform(y_1, y_2);
    points[1][0].x = rng.uniform(x_1, x_2);
    points[1][0].y = rng.uniform(y_1, y_2);
    points[1][1].x = rng.uniform(x_1, x_2);
    points[1][1].y = rng.uniform(y_1, y_2);
    points[1][2].x = rng.uniform(x_1, x_2);
    points[1][2].y = rng.uniform(y_1, y_2);
    const cv::Point* p_points[2] = {points[0], points[1]};
    int numpoints[] = {3, 3};
    cv::fillPoly( image, p_points, numpoints, 2, RandomColor(rng), linetype );
    cv::imshow( windowname, image );
    if( cv::waitKey(kDefDelay) >= 0 ) {
      return true;
    }
  }
  return false;
}

bool DrawRandomCircles(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  int32_t linetype = 8;
  for (int32_t i = 0; i < kDefAnimFrameNum; i++) {
    cv::Point center;
    center.x = rng.uniform(x_1, x_2);
    center.y = rng.uniform(y_1, y_2);
    cv::circle( image, center, rng.uniform(0, 300), RandomColor(rng),
                rng.uniform(-1, 9), linetype );
    cv::imshow( windowname, image );
    if( cv::waitKey(kDefDelay) >= 0 )
      return true;
  }
  return false;
}

bool DisplayRandomText(cv::Mat &image, std::string windowname, cv::RNG &rng) {
  int32_t linetype = 8;
  for(int32_t i = 1; i < kDefAnimFrameNum; i++) {
    cv::Point origin;
    origin.x = rng.uniform(x_1, x_2);
    origin.y = rng.uniform(y_1, y_2);
    cv::putText(image, "Testing text rendering", origin, rng.uniform(0, 8),
                rng.uniform(0, 100) * 0.05 + 0.1, RandomColor(rng),
                rng.uniform(1, 10), linetype);
    cv::imshow(windowname, image);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

bool DisplayBigEnd(cv::Mat &image, std::string windowname) {
  cv::Size textsize = cv::getTextSize("OpenCV forever!",
                                      cv::FONT_HERSHEY_COMPLEX, 3, 5, 0);
  cv::Point origin((kDefWindowWidth - textsize.width)/ 2,
                   (kDefWindowHeight - textsize.height) / 2);
  int32_t linetype = 8;
  cv::Mat image2;
  for(int32_t i = 0; i < 255; i += 2) {
    image2 = image - cv::Scalar::all(i);
    cv::putText(image2, "OpenCV forever!", origin, cv::FONT_HERSHEY_COMPLEX,
                3, cv::Scalar(i, i, 255), 5, linetype);
    cv::imshow(windowname, image2);
    if(0 <= cv::waitKey(kDefDelay))
      return true;
  }
  return false;
}

/*=== Global Function Implementation ========================================*/

int main(int argc, char *argv[]) {
  /* Initialize */
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;

  bool is_keypushed = false; // 終了チェック

  std::string windowname = "Drawing_2"; // ウィンドウ名
  cv::RNG rng(0xFFFFFFFF); // 乱数発生器

  /* 画像を黒の塗りつぶしで初期化 */
  cv::Mat image = cv::Mat::zeros(kDefWindowHeight, kDefWindowWidth, CV_8UC3);
  cv::imshow(windowname, image);
  cv::waitKey(kDefDelay);

  /* ランダムにプリミティブを描画してアニメーション */

  is_keypushed = DrawRandomLines(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DrawRandomRectangles(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DrawRandomEllipses(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DrawRandomPolylines(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DrawRandomFilledPolygons(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DrawRandomCircles(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DisplayRandomText(image, windowname, rng);
  if(is_keypushed)
    return EXIT_FAILURE;

  is_keypushed = DisplayBigEnd(image, windowname);
  if(is_keypushed)
    return EXIT_FAILURE;

  cv::waitKey(0);

  /* Finalize */
  google::InstallFailureSignalHandler();

  return EXIT_SUCCESS;
}
