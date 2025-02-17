<?php

use Illuminate\Support\Str;

return [

    /*
    |--------------------------------------------------------------------------
    | Default Database Connection Name
    |--------------------------------------------------------------------------
    |
    | Here you may specify which of the database connections below you wish
    | to use as your default connection for all database work. Of course
    | you may use many connections at once using the Database library.
    |
    */

    'default' => secureEnv('DB_CONNECTION', 'mysql'),

    /*
    |--------------------------------------------------------------------------
    | Database Connections
    |--------------------------------------------------------------------------
    |
    | Here are each of the database connections setup for your application.
    | Of course, examples of configuring each database platform that is
    | supported by Laravel is shown below to make development simple.
    |
    |
    | All database work in Laravel is done through the PHP PDO facilities
    | so make sure you have the driver for your particular database of
    | choice installed on your machine before you begin development.
    |
    */

    'connections' => [

        'sqlite' => [
            'driver' => 'sqlite',
            'url' => secureEnv('DATABASE_URL'),
            'database' => secureEnv('DB_DATABASE', database_path('database.sqlite')),
            'prefix' => '',
            'foreign_key_constraints' => secureEnv('DB_FOREIGN_KEYS', true),
        ],

        'mysql' => [
            'driver' => 'mysql',
            'url' => secureEnv('DATABASE_URL'),
            'host' => secureEnv('DB_HOST', '127.0.0.1'),
            'port' => secureEnv('DB_PORT', '3306'),
            'database' => secureEnv('DB_DATABASE', 'forge'),
            'username' => secureEnv('DB_USERNAME', 'forge'),
            'password' => secureEnv('DB_PASSWORD', ''),
            'unix_socket' => secureEnv('DB_SOCKET', ''),
            'charset' => 'utf8mb4',
            'collation' => 'utf8mb4_unicode_ci',
            'prefix' => '',
            'prefix_indexes' => true,
            'strict' => true,
            'engine' => null,
            'options' => extension_loaded('pdo_mysql') ? array_filter([
                PDO::MYSQL_ATTR_SSL_CA => secureEnv('MYSQL_ATTR_SSL_CA'),
            ]) : [],
        ],

        'pgsql' => [
            'driver' => 'pgsql',
            'url' => secureEnv('DATABASE_URL'),
            'host' => secureEnv('DB_HOST', '127.0.0.1'),
            'port' => secureEnv('DB_PORT', '5432'),
            'database' => secureEnv('DB_DATABASE', 'forge'),
            'username' => secureEnv('DB_USERNAME', 'forge'),
            'password' => secureEnv('DB_PASSWORD', ''),
            'charset' => 'utf8',
            'prefix' => '',
            'prefix_indexes' => true,
            'search_path' => 'public',
            'sslmode' => 'prefer',
        ],

        'sqlsrv' => [
            'driver' => 'sqlsrv',
            'url' => secureEnv('DATABASE_URL'),
            'host' => secureEnv('DB_HOST', 'localhost'),
            'port' => secureEnv('DB_PORT', '1433'),
            'database' => secureEnv('DB_DATABASE', 'forge'),
            'username' => secureEnv('DB_USERNAME', 'forge'),
            'password' => secureEnv('DB_PASSWORD', ''),
            'charset' => 'utf8',
            'prefix' => '',
            'prefix_indexes' => true,
            // 'encrypt' => secureEnv('DB_ENCRYPT', 'yes'),
            // 'trust_server_certificate' => secureEnv('DB_TRUST_SERVER_CERTIFICATE', 'false'),
        ],

    ],

    /*
    |--------------------------------------------------------------------------
    | Migration Repository Table
    |--------------------------------------------------------------------------
    |
    | This table keeps track of all the migrations that have already run for
    | your application. Using this information, we can determine which of
    | the migrations on disk haven't actually been run in the database.
    |
    */

    'migrations' => 'migrations',

    /*
    |--------------------------------------------------------------------------
    | Redis Databases
    |--------------------------------------------------------------------------
    |
    | Redis is an open source, fast, and advanced key-value store that also
    | provides a richer body of commands than a typical key-value system
    | such as APC or Memcached. Laravel makes it easy to dig right in.
    |
    */

    'redis' => [

        'client' => secureEnv('REDIS_CLIENT', 'phpredis'),

        'options' => [
            'cluster' => secureEnv('REDIS_CLUSTER', 'redis'),
            'prefix' => secureEnv('REDIS_PREFIX', Str::slug(secureEnv('APP_NAME', 'laravel'), '_').'_database_'),
        ],

        'default' => [
            'url' => secureEnv('REDIS_URL'),
            'host' => secureEnv('REDIS_HOST', '127.0.0.1'),
            'username' => secureEnv('REDIS_USERNAME'),
            'password' => secureEnv('REDIS_PASSWORD'),
            'port' => secureEnv('REDIS_PORT', '6379'),
            'database' => secureEnv('REDIS_DB', '0'),
        ],

        'cache' => [
            'url' => secureEnv('REDIS_URL'),
            'host' => secureEnv('REDIS_HOST', '127.0.0.1'),
            'username' => secureEnv('REDIS_USERNAME'),
            'password' => secureEnv('REDIS_PASSWORD'),
            'port' => secureEnv('REDIS_PORT', '6379'),
            'database' => secureEnv('REDIS_CACHE_DB', '1'),
        ],

    ],

];
