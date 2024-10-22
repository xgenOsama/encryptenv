<?php

return [

    /*
    |--------------------------------------------------------------------------
    | Third Party Services
    |--------------------------------------------------------------------------
    |
    | This file is for storing the credentials for third party services such
    | as Mailgun, Postmark, AWS and more. This file provides the de facto
    | location for this type of information, allowing packages to have
    | a conventional file to locate the various service credentials.
    |
    */

    'mailgun' => [
        'domain' => secureEnv('MAILGUN_DOMAIN'),
        'secret' => secureEnv('MAILGUN_SECRET'),
        'endpoint' => secureEnv('MAILGUN_ENDPOINT', 'api.mailgun.net'),
        'scheme' => 'https',
    ],

    'postmark' => [
        'token' => secureEnv('POSTMARK_TOKEN'),
    ],

    'ses' => [
        'key' => secureEnv('AWS_ACCESS_KEY_ID'),
        'secret' => secureEnv('AWS_SECRET_ACCESS_KEY'),
        'region' => secureEnv('AWS_DEFAULT_REGION', 'us-east-1'),
    ],

];
