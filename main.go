package main

import (
	"flag"
	"github.com/GeertJohan/go.rice"
	"log"
	"net/http"
)

var addr = flag.String("addr", ":8080", "http service address")

var fs http.Handler
var box *rice.Box

func init() {
	box = rice.MustFindBox("ui")
	fs = http.FileServer(box.HTTPBox())
}

func static(w http.ResponseWriter, r *http.Request) {
	log.Println(r.URL)
	if r.Method != "GET" {
		http.Error(w, "Method not allowed", http.StatusMethodNotAllowed)
		return
	}

	switch r.URL.Path {
	case "/":
		index := box.MustBytes("/chat.html")
		w.WriteHeader(http.StatusOK)
		w.Header().Set(`Content-Type`, `text/html; charset=utf-8`)
		w.Write(index)
	default:
		fs.ServeHTTP(w, r)
	}
}

func main() {
	flag.Parse()
	hub := newHub()
	go hub.run()
	http.HandleFunc("/", static)
	http.HandleFunc("/ws", func(w http.ResponseWriter, r *http.Request) {
		log.Println(r.URL)
		serveWs(hub, w, r)
	})
	log.Println("Running on ", *addr)
	err := http.ListenAndServe(*addr, nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}
