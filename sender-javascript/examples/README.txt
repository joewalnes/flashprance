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
