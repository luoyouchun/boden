path: tree/master/framework/net/include/bdn/
source: HTTPResponse.h

# HTTPResponse

Represents a response to an [`HTTPRequest`](http_request.md).

## Declaration

```C++
class HTTPResponse
```

## Fields

* **[HTTPRequest](./http_request) originalRequest**
	
	The request that resulted in the given response.

* **int responseCode**
	
	The [HTTP reponse code](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) returned by the server.

* **[String](../foundation/string.md) url**

	The actual URL. This might be different from the requested URL, e.g. due to redirects.

* **[String](../foundation/string.md) header**

	The HTTP header returned by the server.

* **[String](../foundation/string.md) data**

	The data in the HTTP response's body returned by the server.
