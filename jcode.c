int gcode_process_line( char *l ) {
    switch( l[0] ) {
        case 'G':
            switch( l[1] ) {
                case '0':
                    switch( l[2] ) {
                        case ' ': // G0 - fast move ( interpolated ) : G0 F3600 X23.039 Y87.45 Z0.3
                            //
                            break;
                    } break;
                case '1':
                    switch( l[2] ) {
                        case ' ': // G1 - linear move : G1 F1800 X23.813 Y87.291 E0.01486
                            //
                            break;
                    } break;
                case '2':
                    switch( l[2] ) {
                        case ' ': // G2 - clockwise arc : G2 ...
                            //
                            break;
                        case '8':
                            switch( l[3] ) {
                                case ' ': // G28 - go home : G28
                                    //
                                    break;
                            } break;
                    } break;
                case '3':
                    switch( l[2] ) {
                        case ' ': // G3 - counter-clockwise arc : G3 ...
                            //
                            break;
                    } break;
                case '9':
                    switch( l[2] ) {
                        case '2':
                            switch( l[3] ) {
                                case ' ': // G92 - set position : G92 E0
                                    //
                                    break;
                            } break;
                    } break;
            } break;
        case 'M':
            switch( l[1] ) {
                case '0':
                    switch( l[2] ) {
                        case ' ': // M0 - stop : M0
                            //
                            break;
                    } break;
                case '1':
                    switch( l[2] ) {
                        case '0':
                            switch( l[3] ) {
                                case '4':
                                    switch( l[4] ) {
                                        case ' ': // M104 - extruder temperature : M104 S205
                                            //
                                            break;
                                    } break;
                                case '6':
                                    switch( l[4] ) {
                                        case ' ': // M106 - FAN ON : M106
                                            //
                                            break;
                                    } break;
                                case '7':
                                    switch( l[4] ) {
                                        case ' ': // M107 - FAN OFF : M107
                                            //
                                            break;
                                    } break;
                                case '9':
                                    switch( l[4] ) {
                                        case ' ': // M109 - extruder temperature and wait : M109 S205
                                            //
                                            break;
                                    } break;
                            } break;
                        case '4':
                            switch( l[3] ) {
                                case '0':
                                    switch( l[4] ) {
                                        case ' ': // M140 - bed temperature : M109 S205
                                            //
                                            break;
                                    } break;
                            break;
                        case '7':
                            switch( l[3] ) {
                                case ' ': // M17 - enable motors : M17
                                    //
                                    break;
                            } break;
                        case '8':
                            switch( l[3] ) {
                                case ' ': // M18 - disable motors : M18
                                    //
                                    break;
                            } break;
                    }
                    break;
                case '8':
                    switch( l[2] ) {
                        case '4':
                            switch( l[3] ) {
                                case ' ': // M84 - do nothing ;)   : M84
                                    //
                                    break;
                            } break;
                    } break;

            }
            break;
    }
    return 0;
}

