/*=============================================================================
 * Project : Drawing1
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
static const int32_t kDefWindowSize = 400;   /**< ウィンドサイズ */


/*=== Local Variable ========================================================*/

/*=== Local Function Define =================================================*/
/** 楕円の描画
 * @param image 描画対象画像
 * @param angle 楕円のx軸からの傾き
 */
void DrawEllipse(cv::Mat &image, double_t angle);

/** 塗りつぶされた円の描画
 * @param image 描画対象画像
 * @param center 円の中心
 */
void DrawFilledCircle(cv::Mat &image, cv::Point center);

/** ポリゴンの描画
 * @param image 描画対象画像
 */
void DrawPolygon(cv::Mat &image);

/** 線分の描画
 * @param image 描画対象画像
 * @param start 始点
 * @param end 終点
 */
void DrawLine(cv::Mat &image, cv::Point start, cv::Point end);

/*=== Local Function Implementation =========================================*/
void DrawEllipse(cv::Mat &image, double_t angle) {
  int32_t thickness = 2;
  int32_t linetype = 8;
  cv::RotatedRect rotatedrect = cv::RotatedRect(
                                  cv::Point(kDefWindowSize / 2, kDefWindowSize / 2),
                                  cv::Size(kDefWindowSize / 4, kDefWindowSize / 16),
                                  angle);
  cv::ellipse(image, rotatedrect, cv::Scalar(255, 0, 0), thickness, linetype);
}

void DrawFilledCircle(cv::Mat &image, cv::Point center) {
  int32_t thickness = -1;
  int32_t linetype = 8;
  cv::circle(image, center, kDefWindowSize / 32, cv::Scalar(0, 0, 255),
             thickness, linetype);
}

void DrawPolygon(cv::Mat &image) {
  int32_t linetype = 8;
  /* 頂点群の作成 */
  cv::Point rookpoints[1][20];
  rookpoints[0][0] = cv::Point(kDefWindowSize / 4,         7 * kDefWindowSize / 8);
  rookpoints[0][1] = cv::Point(3 * kDefWindowSize / 4,     7 * kDefWindowSize / 8);
  rookpoints[0][2] = cv::Point(3 * kDefWindowSize / 4,     13 * kDefWindowSize / 16);
  rookpoints[0][3] = cv::Point(11 * kDefWindowSize / 16,   13 * kDefWindowSize / 16);
  rookpoints[0][4] = cv::Point(19 * kDefWindowSize / 32,   3 * kDefWindowSize / 8);
  rookpoints[0][5] = cv::Point(3 * kDefWindowSize / 4,     3 * kDefWindowSize / 8);
  rookpoints[0][6] = cv::Point(3 * kDefWindowSize / 4,     kDefWindowSize / 8);
  rookpoints[0][7] = cv::Point(26 * kDefWindowSize / 40,   kDefWindowSize / 8);
  rookpoints[0][8] = cv::Point(26 * kDefWindowSize / 40,   kDefWindowSize / 4);
  rookpoints[0][9] = cv::Point(22 * kDefWindowSize / 40,   kDefWindowSize / 4);
  rookpoints[0][10] = cv::Point(22 * kDefWindowSize / 40,  kDefWindowSize / 8);
  rookpoints[0][11] = cv::Point(18 * kDefWindowSize / 40,  kDefWindowSize / 8);
  rookpoints[0][12] = cv::Point(18 * kDefWindowSize / 40,  kDefWindowSize / 4);
  rookpoints[0][13] = cv::Point(14 * kDefWindowSize / 40,  kDefWindowSize / 4);
  rookpoints[0][14] = cv::Point(14 * kDefWindowSize / 40,  kDefWindowSize / 8);
  rookpoints[0][15] = cv::Point(kDefWindowSize / 4,        kDefWindowSize / 8);
  rookpoints[0][16] = cv::Point(kDefWindowSize / 4,        3 * kDefWindowSize / 8);
  rookpoints[0][17] = cv::Point(13 * kDefWindowSize / 32,  3 * kDefWindowSize / 8);
  rookpoints[0][18] = cv::Point(5 * kDefWindowSize / 16,   13 * kDefWindowSize / 16);
  rookpoints[0][19] = cv::Point(kDefWindowSize / 4,        13 * kDefWindowSize / 16);

  const cv::Point *p_points[1] = {rookpoints[0]};
  int32_t numpoints[] = {20};
  cv::fillPoly(image, p_points, numpoints, 1, cv::Scalar(255, 255, 255), linetype);

}

void DrawLine(cv::Mat &image, cv::Point start, cv::Point end) {
  int32_t thickness = 2;
  int32_t linetype = 8;
  cv::line(image, start, end, cv::Scalar(0, 0, 0), thickness, linetype);
}

/*=== Global Function Implementation ========================================*/

int main(int argc, char *argv[]) {
  /* Initialize */
  google::InitGoogleLogging(argv[0]);

  /* ウィンドウ名 */
  std::string atomwindow = "Drawing 1: Atom";
  std::string rookwindow = "Drawing 2: Rook";

  /* 黒の塗りつぶし画像作成 */
  cv::Mat atomimage = cv::Mat::zeros(kDefWindowSize, kDefWindowSize, CV_8UC3);
  cv::Mat rookimage = cv::Mat::zeros(kDefWindowSize, kDefWindowSize, CV_8UC3);

  /* Step1 : Atom描画
   * 1.a : 楕円描画
   */
  DrawEllipse(atomimage, 90);
  DrawEllipse(atomimage, 0);
  DrawEllipse(atomimage, 45);
  DrawEllipse(atomimage, -45);

  /* 1.b : 円描画 */
  DrawFilledCircle(atomimage, cv::Point(kDefWindowSize / 2, kDefWindowSize / 2));

  /* Step2 : Rook描画
   * 2.a 凸ポリゴン描画
   */
  DrawPolygon(rookimage);

  /* 2.b 矩形作成 */
  cv::rectangle(rookimage, cv::Point(0, 7 * kDefWindowSize / 8),
                cv::Point(kDefWindowSize, kDefWindowSize), cv::Scalar(0, 255, 255),
                -1, 8);
  /* 2.c 線分描画 */
  DrawLine(rookimage, cv::Point(0, 15 * kDefWindowSize / 16),
           cv::Point(kDefWindowSize, 15 * kDefWindowSize / 16));
  DrawLine(rookimage, cv::Point(kDefWindowSize/ 4, 7 * kDefWindowSize / 8),
           cv::Point(kDefWindowSize / 4, kDefWindowSize));
  DrawLine(rookimage, cv::Point(kDefWindowSize/ 2, 7 * kDefWindowSize / 8),
           cv::Point(kDefWindowSize / 2, kDefWindowSize));
  DrawLine(rookimage, cv::Point(3 * kDefWindowSize/ 4, 7 * kDefWindowSize / 8),
           cv::Point(3 * kDefWindowSize / 4, kDefWindowSize));
  /* Step3 : 描画結果の表示 */
  cv::imshow(atomwindow, atomimage);
  cv::moveWindow(atomwindow, 0, 200);
  cv::imshow(rookwindow, rookimage);
  cv::moveWindow(rookwindow, kDefWindowSize, 200);

  cv::waitKey(0);

  cv::imwrite("atomresult.png", atomimage);
  cv::imwrite("rookresult.png", rookimage);

  /* Finalize */
  google::InstallFailureSignalHandler();

  return EXIT_SUCCESS;
}
