FROM builder-2024-05:ver_1 AS built

FROM ubuntu:latest
COPY --from=built /app/Collector/Bin/collector /app/collector

EXPOSE 8080

CMD ["/app/collector"]

