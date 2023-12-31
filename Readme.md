MariaDB UDF for xxhash64, xxhash32 and xxhash32-signed
======================================================
This is a set of 3 UDFs that can be installed in MariaDB.

  - `xxhash64('string')` -> returns signed 64bit int (UDF can return only signed `long long`)
  - `xxhash32('string')` -> returns unsigned 32bit int
  - `xxhash32s('string')` -> returns signed 32bit int

My main use-case for these is to produce `integer primary key` from long `string`.

Dependencies
------------
To compile the `mariadb-xxhash.so`, first you need to install `libxxhash-dev`.
It brings static version of the library and header files.
You will need headers for `mariadb` as well.

`sudo apt install libxxhash-dev libmariadb-dev libmariadbd-dev`

You will need compiler too.

`sudo apt install make gcc g++`

Build
-----
To build the `mariadb-xxhash.so` library use:

`make`

If you find something is wrong with the compiling/linking feel free to edit `Makefile`
Upon success you should have a fresh copy of `mariadb-xxhash.so`, which is statically linked to `libxxhash`.

Installing
----------
Installation is just copying `mariadb-xxhash.so` to `/usr/lib/mysql/plugin`

`make install`

Installing in MariaDB
---------------------
You can install the UDFs in a particular database or for the whole server.

```
CREATE FUNCTION xxhash32 RETURNS INTEGER SONAME "mariadb-xxhash.so";
CREATE FUNCTION xxhash32s RETURNS INTEGER SONAME "mariadb-xxhash.so";
CREATE FUNCTION xxhash64 RETURNS INTEGER SONAME "mariadb-xxhash.so";
```

Testing in MariaDB
---------------------

```
MariaDB> SELECT xxhash32('');
+--------------+
| xxhash32('') |
+--------------+
|     46947589 |
+--------------+
1 row in set (0.000 sec)
```

