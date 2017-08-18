####################################################################################################
##
##  Project:  Embedded Learning Library (ELL)
##  File:     darknet_import.py (importers)
##  Authors:  Chris Lovett
##
##  Requires: Python 3.x
##
####################################################################################################

import sys
import os
import numpy as np
import cv2
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), '../utilities/pythonlibs'))
import find_ell
import darknet_to_ell
import ell_utilities
import json

class DarknetImporter():
    
    def __init__(self):
        self.model_file = None
        self.config_file = None

    def parse_command_line(self, args):
        if (len(args) != 3):
            return False

        self.config_file = args[1]
        if (not os.path.isfile(self.config_file)):
            print("config file '%s' not found" % (self.config_file))
            return False

        self.model_file = args[2]
        if (not os.path.isfile(self.model_file)):
            print("model file '%s' not found" % (self.model_file))
            return False
            
        return True

    def print_usage(self):
        print("Usage darknet_import configFile weightsFile")
        print("Converts darknet model to ELL model")
        print("Example:")
        print("    darknet_import darknet.cfg darknet.weights")
        print("This outputs 'darknet.model' and 'darknet_config.json'")
        return

    def run(self):
        predictor = darknet_to_ell.predictor_from_darknet_model(self.config_file, self.model_file)

        input_shape = predictor.GetInputShape()
        output_shape = predictor.GetOutputShape()
        
        model_file_name = os.path.splitext(self.model_file)[0]+'.ellmodel'
        head, tail = os.path.split(self.model_file)

        ell_map = ell_utilities.ell_map_from_float_predictor(predictor)
        print("Saving model file: '" + model_file_name + "'")
        ell_map.Save(model_file_name)

        model_config = {
            'model': tail,
            'input_rows': input_shape.rows,
            'input_columns': input_shape.columns,
            'input_channels': input_shape.channels,
            'output_rows': output_shape.rows,
            'output_columns': output_shape.columns,
            'output_channels': output_shape.channels
        }

        config_file_name = os.path.splitext(self.model_file)[0]+'_config.json'
        config_json = json.dumps(model_config, indent=2, sort_keys=True)

        print("Saving config file: '" + config_file_name + "'")
        with open(config_file_name, 'w') as f:
            f.write(config_json)
            f.close()

        print(config_json)

if __name__ == "__main__":
    importer = DarknetImporter()
    if (not importer.parse_command_line(sys.argv)):
        importer.print_usage()
    else:
        importer.run()


