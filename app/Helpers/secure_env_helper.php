<?php
// app/Helpers/env_helper.php

function secureEnv(string $key, $defualt = null): ?string
{
    // Load the shared object
    $ffi = FFI::cdef(
        "char* get_env_value(const char* key);", 
        base_path('env.so') // Adjust the path to where your env.so is located
    );

    // Call the C function
    $result = $ffi->get_env_value($key);

    // Convert the C string to a PHP string and return it
    return $result ? FFI::string($result) : $defualt;
}
