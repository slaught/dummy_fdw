-- create wrapper with handler
CREATE OR REPLACE FUNCTION dummy_handler ()
RETURNS fdw_handler
AS 'BUILD_DIR/dummy_data.so'
LANGUAGE C STRICT;

CREATE FOREIGN DATA WRAPPER dummy_data
HANDLER dummy_handler;

create server amazon_s3 foreign data wrapper dummy_data
options (
  wrapper 's3fdw.s3fdw.S3Fdw'
);


CREATE USER MAPPING FOR public SERVER amazon_s3
;

CREATE FOREIGN TABLE stats(
  dvalue date,
  email varchar,
  hour interval,
  login_time interval,
  logout_time interval,
  available_time interval
) SERVER amazon_s3
OPTIONS (
  hostname 's3.amazonaws.com',
  bucketname 'reports',
  filename 'hourly.csv',
  format 'csv',
  delimiter E',',
  quote E'"',
  header 'true'
);

select * from stats;

