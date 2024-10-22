<?php
// app/Helpers/env_helper.php

function secureEnv(string $key, $default = null): ?string
{
    // Load the shared object
    $ffi = FFI::cdef(
        "char* get_env_value(const char* key);", 
        base_path('env.so') // Adjust the path to where your env.so is located
    );

    // Call the C function
    $result = $ffi->get_env_value($key);
    // Convert the C string to a PHP string
    $envValue = $result ? FFI::string($result) : $default;
    // Check if the result is null
    if ($result === null) {
        return $default; // Return default if the result is null
    }
    // Check for pattern matches
    if (preg_match('/^"\\${([A-Z_]+)}"$/', $envValue, $matches)) {
        // The matched variable name
        $variableName = $matches[1];
        // Call secureEnv again if you want to retrieve the value of the matched variable
        return secureEnv($variableName);
    }

    return $envValue; // Return the original value if no pattern matched
}
