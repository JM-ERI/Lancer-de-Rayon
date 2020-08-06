/* ===============================================================
  E.Incerti - Université de Marne-la-Vallée - incerti@univ-mlv.fr 
       - Librairie G3X - Fonctions de base d'accès public -           
                    version 5.0 - Dec.2012                                           
  ============================================================= */

#ifdef __cplusplus
  extern "C" {
#else
  #define _GNU_SOURCE
#endif

#ifndef _G3X_COLORS_H
  #define _G3X_COLORS_H
  
  /* TRANSPARENCE 0.00                                       */
  /* intensité 100%                                          */
  #define G3Xw    (const float[4]){1.00,1.00,1.00,1.00} /* blanc   */
  #define G3Xr    (const float[4]){1.00,0.00,0.00,1.00} /* rouge   */
  #define G3Xo    (const float[4]){1.00,0.50,0.00,1.00} /* orange  */
  #define G3Xy    (const float[4]){1.00,1.00,0.00,1.00} /* jaune   */
  #define G3Xg    (const float[4]){0.00,1.00,0.00,1.00} /* vert    */
  #define G3Xc    (const float[4]){0.00,1.00,1.00,1.00} /* cyan    */
  #define G3Xb    (const float[4]){0.00,0.00,1.00,1.00} /* bleu    */
  #define G3Xm    (const float[4]){1.00,0.00,1.00,1.00} /* magenta */
  #define G3Xk    (const float[4]){0.00,0.00,0.00,1.00} /* noir    */
  /* intensité  75%                                          */
  #define G3Xwa   (const float[4]){0.75,0.75,0.75,1.00} /*         */
  #define G3Xra   (const float[4]){0.75,0.00,0.00,1.00} /*         */
  #define G3Xya   (const float[4]){0.75,0.75,0.00,1.00} /*         */
  #define G3Xga   (const float[4]){0.00,0.75,0.00,1.00} /*         */
  #define G3Xca   (const float[4]){0.00,0.75,0.75,1.00} /*         */
  #define G3Xba   (const float[4]){0.00,0.00,0.75,1.00} /*         */
  #define G3Xma   (const float[4]){0.75,0.00,0.75,1.00} /*         */
  /* intensité  50%                                          */
  #define G3Xwb   (const float[4]){0.50,0.50,0.50,1.00} /*         */
  #define G3Xrb   (const float[4]){0.50,0.12,0.12,1.00} /*         */
  #define G3Xyb   (const float[4]){0.50,0.50,0.12,1.00} /*         */
  #define G3Xgb   (const float[4]){0.12,0.50,0.12,1.00} /*         */
  #define G3Xcb   (const float[4]){0.12,0.50,0.50,1.00} /*         */
  #define G3Xbb   (const float[4]){0.12,0.12,0.50,1.00} /*         */
  #define G3Xmb   (const float[4]){0.50,0.12,0.50,1.00} /*         */
  /* intensité  25%                                          */
  #define G3Xwc   (const float[4]){0.25,0.25,0.25,1.00} /*         */
  #define G3Xrc   (const float[4]){0.25,0.12,0.12,1.00} /*         */
  #define G3Xyc   (const float[4]){0.25,0.25,0.12,1.00} /*         */
  #define G3Xgc   (const float[4]){0.12,0.25,0.12,1.00} /*         */
  #define G3Xcc   (const float[4]){0.12,0.25,0.25,1.00} /*         */
  #define G3Xbc   (const float[4]){0.12,0.12,0.25,1.00} /*         */
  #define G3Xmc   (const float[4]){0.25,0.12,0.25,1.00} /*         */
  /* intensité  12.5%                                        */
  #define G3Xwd   (const float[4]){0.12,0.12,0.12,1.00} /*         */
  #define G3Xrd   (const float[4]){0.12,0.06,0.06,1.00} /*         */
  #define G3Xyd   (const float[4]){0.12,0.12,0.06,1.00} /*         */
  #define G3Xgd   (const float[4]){0.06,0.12,0.06,1.00} /*         */
  #define G3Xcd   (const float[4]){0.06,0.12,0.12,1.00} /*         */
  #define G3Xbd   (const float[4]){0.06,0.06,0.12,1.00} /*         */
  #define G3Xmd   (const float[4]){0.12,0.06,0.12,1.00} /*         */


  /* TRANSPARENCE 0.25                                       */
  /* intensité 100%                                          */
  #define G3Xw_a  (const float[4]){1.00,1.00,1.00,0.75} /* blanc   */
  #define G3Xr_a  (const float[4]){1.00,0.00,0.00,0.75} /* rouge   */
  #define G3Xo_a  (const float[4]){1.00,0.50,0.00,0.75} /* orange  */
  #define G3Xy_a  (const float[4]){1.00,1.00,0.00,0.75} /* jaune   */
  #define G3Xg_a  (const float[4]){0.00,1.00,0.00,0.75} /* vert    */
  #define G3Xc_a  (const float[4]){0.00,1.00,1.00,0.75} /* cyan    */
  #define G3Xb_a  (const float[4]){0.00,0.00,1.00,0.75} /* bleu    */
  #define G3Xm_a  (const float[4]){1.00,0.00,1.00,0.75} /* magenta */
  #define G3Xk_a  (const float[4]){0.00,0.00,0.00,0.75} /* noir    */
  /* intensité  75%                                          */
  #define G3Xwa_a (const float[4]){0.75,0.75,0.75,0.75} /*         */
  #define G3Xra_a (const float[4]){0.75,0.00,0.00,0.75} /*         */
  #define G3Xya_a (const float[4]){0.75,0.75,0.00,0.75} /*         */
  #define G3Xga_a (const float[4]){0.00,0.75,0.00,0.75} /*         */
  #define G3Xca_a (const float[4]){0.00,0.75,0.75,0.75} /*         */
  #define G3Xba_a (const float[4]){0.00,0.00,0.75,0.75} /*         */
  #define G3Xma_a (const float[4]){0.75,0.00,0.75,0.75} /*         */
  /* intensité  50%                                          */
  #define G3Xwb_a (const float[4]){0.50,0.50,0.50,0.75} /*         */
  #define G3Xrb_a (const float[4]){0.50,0.12,0.12,0.75} /*         */
  #define G3Xyb_a (const float[4]){0.50,0.50,0.12,0.75} /*         */
  #define G3Xgb_a (const float[4]){0.12,0.50,0.12,0.75} /*         */
  #define G3Xcb_a (const float[4]){0.12,0.50,0.50,0.75} /*         */
  #define G3Xbb_a (const float[4]){0.12,0.12,0.50,0.75} /*         */
  #define G3Xmb_a (const float[4]){0.50,0.12,0.50,0.75} /*         */
  /* intensité  25%                                          */
  #define G3Xwc_a (const float[4]){0.25,0.25,0.25,0.75} /*         */
  #define G3Xrc_a (const float[4]){0.25,0.12,0.12,0.75} /*         */
  #define G3Xyc_a (const float[4]){0.25,0.25,0.12,0.75} /*         */
  #define G3Xgc_a (const float[4]){0.12,0.25,0.12,0.75} /*         */
  #define G3Xcc_a (const float[4]){0.12,0.25,0.25,0.75} /*         */
  #define G3Xbc_a (const float[4]){0.12,0.12,0.25,0.75} /*         */
  #define G3Xmc_a (const float[4]){0.25,0.12,0.25,0.75} /*         */
  /* intensité  12.5%                                        */
  #define G3Xwd_a (const float[4]){0.12,0.12,0.12,0.75} /*         */
  #define G3Xrd_a (const float[4]){0.12,0.06,0.06,0.75} /*         */
  #define G3Xyd_a (const float[4]){0.12,0.12,0.06,0.75} /*         */
  #define G3Xgd_a (const float[4]){0.06,0.12,0.06,0.75} /*         */
  #define G3Xcd_a (const float[4]){0.06,0.12,0.12,0.75} /*         */
  #define G3Xbd_a (const float[4]){0.06,0.06,0.12,0.75} /*         */
  #define G3Xmd_a (const float[4]){0.12,0.06,0.12,0.75} /*         */

  /* TRANSPARENCE 0.50                                       */
  /* intensité 100%                                          */
  #define G3Xw_b  (const float[4]){1.00,1.00,1.00,0.50} /* blanc   */
  #define G3Xr_b  (const float[4]){1.00,0.00,0.00,0.50} /* rouge   */
  #define G3Xo_b  (const float[4]){1.00,0.50,0.00,0.50} /* orange  */
  #define G3Xy_b  (const float[4]){1.00,1.00,0.00,0.50} /* jaune   */
  #define G3Xg_b  (const float[4]){0.00,1.00,0.00,0.50} /* vert    */
  #define G3Xc_b  (const float[4]){0.00,1.00,1.00,0.50} /* cyan    */
  #define G3Xb_b  (const float[4]){0.00,0.00,1.00,0.50} /* bleu    */
  #define G3Xm_b  (const float[4]){1.00,0.00,1.00,0.50} /* magenta */
  #define G3Xk_b  (const float[4]){0.00,0.00,0.00,0.50} /* noir    */
  /* intensité  75%                                          */
  #define G3Xwa_b (const float[4]){0.75,0.75,0.75,0.50} /*         */
  #define G3Xra_b (const float[4]){0.75,0.00,0.00,0.50} /*         */
  #define G3Xya_b (const float[4]){0.75,0.75,0.00,0.50} /*         */
  #define G3Xga_b (const float[4]){0.00,0.75,0.00,0.50} /*         */
  #define G3Xca_b (const float[4]){0.00,0.75,0.75,0.50} /*         */
  #define G3Xba_b (const float[4]){0.00,0.00,0.75,0.50} /*         */
  #define G3Xma_b (const float[4]){0.75,0.00,0.75,0.50} /*         */
  /* intensité  50%                                          */
  #define G3Xwb_b (const float[4]){0.50,0.50,0.50,0.50} /*         */
  #define G3Xrb_b (const float[4]){0.50,0.12,0.12,0.50} /*         */
  #define G3Xyb_b (const float[4]){0.50,0.50,0.12,0.50} /*         */
  #define G3Xgb_b (const float[4]){0.12,0.50,0.12,0.50} /*         */
  #define G3Xcb_b (const float[4]){0.12,0.50,0.50,0.50} /*         */
  #define G3Xbb_b (const float[4]){0.12,0.12,0.50,0.50} /*         */
  #define G3Xmb_b (const float[4]){0.50,0.12,0.50,0.50} /*         */
  /* intensité  25%                                          */
  #define G3Xwc_b (const float[4]){0.25,0.25,0.25,0.50} /*         */
  #define G3Xrc_b (const float[4]){0.25,0.12,0.12,0.50} /*         */
  #define G3Xyc_b (const float[4]){0.25,0.25,0.12,0.50} /*         */
  #define G3Xgc_b (const float[4]){0.12,0.25,0.12,0.50} /*         */
  #define G3Xcc_b (const float[4]){0.12,0.25,0.25,0.50} /*         */
  #define G3Xbc_b (const float[4]){0.12,0.12,0.25,0.50} /*         */
  #define G3Xmc_b (const float[4]){0.25,0.12,0.25,0.50} /*         */
  /* intensité  12.5%                                        */
  #define G3Xwd_b (const float[4]){0.12,0.12,0.12,0.50} /*         */
  #define G3Xrd_b (const float[4]){0.12,0.06,0.06,0.50} /*         */
  #define G3Xyd_b (const float[4]){0.12,0.12,0.06,0.50} /*         */
  #define G3Xgd_b (const float[4]){0.06,0.12,0.06,0.50} /*         */
  #define G3Xcd_b (const float[4]){0.06,0.12,0.12,0.50} /*         */
  #define G3Xbd_b (const float[4]){0.06,0.06,0.12,0.50} /*         */
  #define G3Xmd_b (const float[4]){0.12,0.06,0.12,0.50} /*         */

  /* TRANSPARENCE 0.75                                       */
  /* intensité 100%                                          */
  #define G3Xw_c  (const float[4]){1.00,1.00,1.00,0.25} /* blanc   */
  #define G3Xr_c  (const float[4]){1.00,0.00,0.00,0.25} /* rouge   */
  #define G3Xo_c  (const float[4]){1.00,0.50,0.00,0.25} /* orange  */
  #define G3Xy_c  (const float[4]){1.00,1.00,0.00,0.25} /* jaune   */
  #define G3Xg_c  (const float[4]){0.00,1.00,0.00,0.25} /* vert    */
  #define G3Xc_c  (const float[4]){0.00,1.00,1.00,0.25} /* cyan    */
  #define G3Xb_c  (const float[4]){0.00,0.00,1.00,0.25} /* bleu    */
  #define G3Xm_c  (const float[4]){1.00,0.00,1.00,0.25} /* magenta */
  #define G3Xk_c  (const float[4]){0.00,0.00,0.00,0.25} /* noir    */
  /* intensité  75%                                          */
  #define G3Xwa_c (const float[4]){0.75,0.75,0.75,0.25} /*         */
  #define G3Xra_c (const float[4]){0.75,0.00,0.00,0.25} /*         */
  #define G3Xya_c (const float[4]){0.75,0.75,0.00,0.25} /*         */
  #define G3Xga_c (const float[4]){0.00,0.75,0.00,0.25} /*         */
  #define G3Xca_c (const float[4]){0.00,0.75,0.75,0.25} /*         */
  #define G3Xba_c (const float[4]){0.00,0.00,0.75,0.25} /*         */
  #define G3Xma_c (const float[4]){0.75,0.00,0.75,0.25} /*         */
  /* intensité  50%                                          */
  #define G3Xwb_c (const float[4]){0.50,0.50,0.50,0.25} /*         */
  #define G3Xrb_c (const float[4]){0.50,0.12,0.12,0.25} /*         */
  #define G3Xyb_c (const float[4]){0.50,0.50,0.12,0.25} /*         */
  #define G3Xgb_c (const float[4]){0.12,0.50,0.12,0.25} /*         */
  #define G3Xcb_c (const float[4]){0.12,0.50,0.50,0.25} /*         */
  #define G3Xbb_c (const float[4]){0.12,0.12,0.50,0.25} /*         */
  #define G3Xmb_c (const float[4]){0.50,0.12,0.50,0.25} /*         */
  /* intensité  25%                                          */
  #define G3Xwc_c (const float[4]){0.25,0.25,0.25,0.25} /*         */
  #define G3Xrc_c (const float[4]){0.25,0.12,0.12,0.25} /*         */
  #define G3Xyc_c (const float[4]){0.25,0.25,0.12,0.25} /*         */
  #define G3Xgc_c (const float[4]){0.12,0.25,0.12,0.25} /*         */
  #define G3Xcc_c (const float[4]){0.12,0.25,0.25,0.25} /*         */
  #define G3Xbc_c (const float[4]){0.12,0.12,0.25,0.25} /*         */
  #define G3Xmc_c (const float[4]){0.25,0.12,0.25,0.25} /*         */
  /* intensité  12.5%                                        */
  #define G3Xwd_c (const float[4]){0.12,0.12,0.12,0.25} /*         */
  #define G3Xrd_c (const float[4]){0.12,0.06,0.06,0.25} /*         */
  #define G3Xyd_c (const float[4]){0.12,0.12,0.06,0.25} /*         */
  #define G3Xgd_c (const float[4]){0.06,0.12,0.06,0.25} /*         */
  #define G3Xcd_c (const float[4]){0.06,0.12,0.12,0.25} /*         */
  #define G3Xbd_c (const float[4]){0.06,0.06,0.12,0.25} /*         */
  #define G3Xmd_c (const float[4]){0.12,0.06,0.12,0.25} /*         */

#endif

#ifdef __cplusplus
  }
#endif
/*=============================================================================*/
