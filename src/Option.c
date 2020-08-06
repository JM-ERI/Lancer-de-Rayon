#include <stddef.h>

#include "../include/Option.h"

int want_fast_output_scene(const Option *options){
    if (options == NULL){
        return -1;
    }
    return options->output_path != NULL;
}
