// Author: Bojan Nikolic <b.nikolic@mrao.cam.ac.uk>
//
// Define symbols for the declared wrapper functions -- the definition
// simply fetches the pointer from Python and calls that.
//

#include <Python.h>

#include "arlwrap.h"

// in: fname: same as the *NamedTuple* containing the FFI memory address of a
// Python routine.
// E.G.: Python routine 'arl_restore_cube_fii', NamedTuple 'arl_restore_cube' =>
// => fname == "arl_restore_cube".
//
// This routine imports the arlwrap.py module, loads the NamedTuple named
// 'fname', and extracts the function address. The address is then returned as
// a callable C function pointer.
size_t bk_getfn(const char* fname)
{
  size_t res=0;
  PyGILState_STATE gilstate = PyGILState_Ensure();
  
  PyObject *m, *pyfn, *fnaddress;
  if(!(  m= PyImport_ImportModule("arlwrap") ))
    goto failed;
  if(!( pyfn = PyObject_GetAttrString(m, fname)))
    goto failed;
  if(!( fnaddress = PyObject_GetAttrString(pyfn, "address")))
    goto failed;

  res=PyNumber_AsSsize_t(fnaddress, NULL);

  PyGILState_Release(gilstate);
  return res;

 failed:
  PyErr_Print();
  PyGILState_Release(gilstate);  
  return 0;

  // Not decrementing references here since unknown when the objects
  // will be used for C layer. Therefore breakin python functions will
  // never get garbage collected. 
}

void arl_initialize(void)
{
  Py_Initialize();
}


// Not a prototype, so warning will be generated. TODO: switch off
// warning for this instance only?
#define BKFNPY(F)  (* ( void (*)() )(bk_getfn( #F ))) 


void helper_get_image_shape(const double *frequency, double cellsize,
		int *shape)
{
        BKFNPY(helper_get_image_shape)(frequency, cellsize, shape);
}

void helper_get_image_shape_multifreq(ARLConf *lowconf, double cellsize,
		int npixel, int *shape)
{
        BKFNPY(helper_get_image_shape_multifreq)(lowconf, cellsize, npixel, shape);
}

void helper_set_image_params(const ARLVis *vis, Image *image) {
	BKFNPY(helper_set_image_params)(vis, image);
}

void arl_invert_2d(const ARLVis *visin, const Image *img_in, bool dopsf, Image *out, double *sumwt)
{
	BKFNPY(arl_invert_2d)(visin, img_in, dopsf, out, sumwt);
}

void arl_create_visibility(ARLConf *lowconf, ARLVis *res_vis)
{
	BKFNPY(arl_create_visibility)(lowconf, res_vis);
}

void arl_create_blockvisibility(ARLConf *lowconf, ARLVis *res_vis)
{
	BKFNPY(arl_create_blockvisibility)(lowconf, res_vis);
}

void arl_advise_wide_field(ARLConf *lowconf, ARLVis *res_vis, ARLadvice *adv)
{
	BKFNPY(arl_advise_wide_field)(lowconf, res_vis, adv);
}



void arl_create_test_image(const double *frequency, double cellsize, char *phasecentre,
		Image *res_img)
{
	BKFNPY(arl_create_test_image)(frequency, cellsize, phasecentre, res_img);
}

void arl_create_low_test_image_from_gleam(ARLConf *lowconf, double cellsize, int npixel, char *phasecentre,
		Image *res_img)
{
	BKFNPY(arl_create_low_test_image_from_gleam)(lowconf, cellsize, npixel, phasecentre, res_img);
}

void arl_copy_visibility(const ARLVis *visin,
			 ARLVis *visout,
			 bool zero)
{
  BKFNPY(arl_copy_visibility)(visin, visout, zero);
}

void arl_predict_2d(const ARLVis *visin, const Image *img, ARLVis *visout) {
	BKFNPY(arl_predict_2d)(visin, img, visout);
}

void arl_create_image_from_visibility(const ARLVis *vis, Image *model) {
	BKFNPY(arl_create_image_from_visibility)(vis, model);
}

void arl_create_image_from_blockvisibility(ARLConf *lowconf, const ARLVis *blockvis, double cellsize, int npixel, char* phasecentre, Image *model){
	BKFNPY(arl_create_image_from_blockvisibility)(lowconf, blockvis, cellsize, npixel, phasecentre, model);
}

void arl_deconvolve_cube(Image *dirty, Image *psf, Image *restored, Image *residual)
{
  BKFNPY(arl_deconvolve_cube)(dirty, psf, restored, residual);
}

void arl_restore_cube(Image *model, Image *psf, Image *residual, Image *restored)
{
  BKFNPY(arl_restore_cube)(model, psf, residual, restored);
}

void helper_get_nbases(char * config_name, ant_t * nbases)
{
  BKFNPY(helper_get_nbases)(config_name, nbases);
}

void helper_get_nbases_rmax(char * config_name, double rmax, ant_t * nbases)
{
  BKFNPY(helper_get_nbases_rmax)(config_name, rmax, nbases);
}

void arl_predict_function(ARLConf *lowconf, const ARLVis *visin, const Image *img, ARLVis *visout, ARLVis *blockvisout, long long int *cindexout) {
	BKFNPY(arl_predict_function)(lowconf, visin, img, visout, blockvisout, cindexout);
}

void arl_invert_function(ARLConf * lowconf, const ARLVis *visin, Image * img_model, int vis_slices, Image * img_dirty){
	BKFNPY(arl_invert_function)(lowconf, visin, img_model, vis_slices, img_dirty);
}

void arl_ical(ARLConf * lowconf, const ARLVis *visin, Image * img_model, int vis_slices, Image * img_deconv, Image * img_resid, Image * img_rest){
	BKFNPY(arl_ical)(lowconf, visin, img_model, vis_slices, img_deconv, img_resid, img_rest);
}


void arl_convert_visibility_to_blockvisibility(ARLConf *lowconf, const ARLVis *visin, const ARLVis *blockvisin, long long int *cindexin, ARLVis *visout) {
	BKFNPY(arl_convert_visibility_to_blockvisibility)(lowconf, visin, blockvisin, cindexin, visout);
}

void arl_create_gaintable_from_blockvisibility(ARLConf *lowconf, const ARLVis *visin, ARLGt *gtout) {
	BKFNPY(arl_create_gaintable_from_blockvisibility)(lowconf, visin, gtout);
}

void arl_apply_gaintable(ARLConf *lowconf, const ARLVis *visin, ARLGt *gtin, ARLVis *visout) {
	BKFNPY(arl_apply_gaintable)(lowconf, visin, gtin, visout);
}

void arl_simulate_gaintable(ARLConf *lowconf, ARLGt *gt) {
	BKFNPY(arl_simulate_gaintable)(lowconf, gt);
}

void arl_predict_function_blockvis(ARLConf * lowconf, ARLVis * visin, const Image * img) {
	BKFNPY(arl_predict_function_blockvis)(lowconf, visin, img);
}


