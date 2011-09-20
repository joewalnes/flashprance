This demo use HTML 5 Application Cache to work in offline mode.

For this to work, you need to:

* Serve up cache.manifest with the mime type 'text/cache-manifest'
  (you'll see errors in the JavaScript console if this isn't the case)

* Ensure that every referenced file is listed in cache.manifest
  (you'll see errors in the JavaScript console if this isn't the case)

* Modify the contents of the file everytime you want to allow the app
  to be refreshed (i.e. whenever you change the code). Simply change
  the comment in cache.manifest to force a change, otherwise the browser
  shall aggressively cache.

There is also a Google AppEngine app.yaml config file - this is to make
local testing easy (just installed the AppEngine Python SDK), and for
hosting the public demo site on <http://flashprance.appspot.com/>.

To run locally:

   dev_appserver.py /path/to/flashprance/sender-javascript/examples
