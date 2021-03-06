#ifndef WRAP_SUPPORT_H
#define WRAP_SUPPORT_H

#include "arlwrap.h"

int export_image_to_fits_c(Image *im, char * filename);
Image *allocate_image(int *shape);
Image *destroy_image(Image *image);
ARLConf *allocate_arlconf_default(const char *conf_name);
ARLVis *allocate_vis_data(int npol, int nvis);
ARLVis *destroy_vis(ARLVis *vis);
#endif
