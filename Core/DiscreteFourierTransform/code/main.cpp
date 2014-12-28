/*=============================================================================
 * Project : DiscreteFourierTransform
 * Code : main.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/12/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * 離散フーリエ変換(DFT)
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <stdint.h>
#include <glog/logging.h>

#include <opencv2/opencv.hpp>

#include <string>

/*=== Local Define / Local Const ============================================*/



/*=== Local Variable ========================================================*/

/*=== Local Function Define =================================================*/


/*=== Local Function Implementation =========================================*/


/*=== Global Function Implementation ========================================*/

int main(int argc, char *argv[]) {
  /* Initialize */
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;


  /* Finalize */
  google::InstallFailureSignalHandler();

  return EXIT_SUCCESS;
}
